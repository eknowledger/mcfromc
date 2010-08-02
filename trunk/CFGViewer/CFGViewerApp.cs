using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Drawing;
using ParserDotNetBridge;
using System.Collections;
using System.Diagnostics;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace CFGViewer
{
    public delegate void MessageDelegate(string message);
    public delegate void ImageUpdateDelegate(string imageFile);
    public delegate void ErrorDelegate(string heading, string err);
    public delegate void MCTextUpdateDelegate(string mcText);

    public class CFGViewerApp
    {
        public event MessageDelegate OnMessage;
        public event ImageUpdateDelegate OnImageUpdate;
        public event ErrorDelegate OnError;
        public event MCTextUpdateDelegate OnMCTextUpdated;

        public CFGViewerApp(MessageDelegate msgDelegator,
                            ImageUpdateDelegate imgDelegator,
                            ErrorDelegate errDelegator)
        {
            OnMessage += msgDelegator;
            OnImageUpdate += imgDelegator;
            OnError += errDelegator;
        }

 
        private bool ReadFlowPoints(string filename, Guid id)
        {
            bool rc = true;
            ArrayList arr = null;
            ArrayList mcNames, mcGraphTexts;
            FlowPoint = new Dictionary<string, VisualFlowPoint>();
            string graphText;
            string mcText;
            arr = CFGParser.GenerateCFG(filename, out graphText, out mcNames, out mcGraphTexts, out mcText);

            string err = CFGParser.GetLastError();
            if (arr != null && err == "")
            {
                foreach (VisualFlowPoint fp in arr)
                {
                    FlowPoint[fp.Name] = fp;
                }
            }
            else {
                rc = false;
            }


            if (rc && graphText != null)
            {
                OnMessage("Writing graph to file");
                WriteGraphToFile(DIGRAPH_FILE, graphText);
                rc = RunDot(id);
            }

            if (rc)
            {
                OnMessage("Writing MC graphs to file");
                for (int i = 0; i < mcNames.Count; ++i)
                {
                    WriteGraphToFile(DIGRAPH_FILE + ".MC_" + (mcNames[i] as string), mcGraphTexts[i] as string);
                }

                OnMCTextUpdated(mcText);
             }

            return rc;
        }

        public void readDotSpec(string filename)
        {
            FlowPointName = new Dictionary<Point, string>();
            StreamReader reader = new StreamReader(filename);
            while (!reader.EndOfStream)
            {
                string line = reader.ReadLine();
                //if not edge
                if (line.IndexOf("->") < 0)
                {
                    int posInd = line.IndexOf("pos");
                    if (posInd >= 0)
                    {
                        posInd += 5;
                        int nextInd = line.IndexOf(',', posInd);
                        string numStr = line.Substring(posInd, nextInd - posInd);
                        int x = -1, y = -1;
                        float fX = -1, fY = -1;
                        float.TryParse(numStr, out fX);
                        x = (int)fX;
                        posInd = nextInd + 1;
                        nextInd = line.IndexOf('\"', posInd);
                        numStr = line.Substring(posInd, nextInd - posInd);
                        float.TryParse(numStr, out fY);
                        y = (int)fY;
                        if (x >= 0 && y >= 0)
                        {
                            line = line.Trim(" \t".ToCharArray());
                            string fpName = line.Substring(0, line.IndexOf(' '));
                            FlowPointName.Add(new Point(x, y), fpName);
                        }
                    }
                    else if (line.IndexOf("graph [bb") >=0) {
                        int startInd = line.IndexOf("0,0,") + 4;
                        int endInd = line.IndexOf(',', startInd);
                        string widthStr = line.Substring(startInd, endInd-startInd);
                        startInd = endInd+1;
                        endInd = line.IndexOf('\"', startInd);
                        string heightStr = line.Substring(startInd, endInd-startInd);
                        float w, h;
                        if (float.TryParse(widthStr, out w) &&
                            float.TryParse(heightStr, out h))
                        {
                            m_ImageSize = new Size((int)w, (int)h);
                        }

                    }
                }
                else //if edge
                {
                    int posInd = line.IndexOf("lp=");
                    string orgLine = line;
                    if (posInd < 0)
                    {
                        if (line[line.Length-1] == '\\')
                        {
                            line = reader.ReadLine();
                            posInd = line.IndexOf("lp=");
                        }
                    }
                    if (posInd >= 0)
                    {
                        posInd += 4;
                        int nextInd = line.IndexOf(',', posInd);
                        string numStr = line.Substring(posInd, nextInd - posInd);
                        int x = -1, y = -1;
                        float fX = -1, fY = -1;
                        float.TryParse(numStr, out fX);
                        x = (int)fX;
                        posInd = nextInd + 1;
                        nextInd = line.IndexOf('\"', posInd);
                        numStr = line.Substring(posInd, nextInd - posInd);
                        float.TryParse(numStr, out fY);
                        y = (int)fY;
                        if (x >= 0 && y >= 0)
                        {
                            int labelStartIndex = orgLine.IndexOf("label=");
                            if (labelStartIndex >= 0)
                            {
                                labelStartIndex += 5;
                                int labelEndIndex = orgLine.IndexOf(",", labelStartIndex);

                                orgLine = orgLine.Trim(" \t".ToCharArray());
                                string fpName = orgLine.Substring(labelStartIndex, labelEndIndex - labelStartIndex - 1);
                                Point key = new Point(x, y);
                                if (!FlowPointName.ContainsKey(key))
                                    FlowPointName.Add(key, fpName);
                            }
                        }
                    }
                }
            }
            reader.Close();
            reader.Dispose();
        }

        public Size ImageSize
        {
            get
            {
                return m_ImageSize;
            }
        }

        public List<Point> Locations
        {
            get
            {
                return FlowPointName.Keys.ToList<Point>();
            }
        }

        public int findOpeningParentheses(string code, int closingIndex)
        {
            int closingCount = 0;

            while (code[closingIndex] != '}') {
                closingIndex--;
            }

            do
            {
                if (code[closingIndex] == '}')
                {
                    closingCount++;
                }
                else if (code[closingIndex] == '{')
                {
                    closingCount--;
                }

                closingIndex--;
            }
            while (closingCount > 0 && closingIndex >= 0);

            return closingIndex;
        }

        public void WriteGraphToFile(string filename, string graphText)
        {
            if (File.Exists(filename)) {
                File.Delete(filename);
            }
            FileStream fstr = File.OpenWrite(filename);
            using (StreamWriter writer = new StreamWriter(fstr))
            {
                writer.AutoFlush = true;
                writer.Write(graphText);
                writer.Flush();
                writer.Close();
                writer.Dispose();
            }
            fstr.Close();
            fstr.Dispose();
        }

        private bool RunDot(Guid id)
        {
            bool rc = true;
            OnMessage("Running dot tool - generating layout");
            ProcessStartInfo startInfo = new ProcessStartInfo(Application.StartupPath + "/../ThirdParty/Graphviz/bin/dot.exe");
            startInfo.WindowStyle = ProcessWindowStyle.Hidden;
            startInfo.Arguments = "-Tdot " + "\"" + DIGRAPH_FILE + "\"" + " -o " + "\"" + DOT_LAYOUT_FILE + "_" + id.ToString() + "\"";
            Process p1 = Process.Start(startInfo);
            p1.WaitForExit();
            rc = (p1.ExitCode == 0);
            if (rc) 
            {
                rc = GenerateDotBitmap(DIGRAPH_FILE, DOT_IMAGE_FILE + "_" + id.ToString() + ".png");
            }
            else
            {
                OnError("dot: layout file creation failed.", null);
            }

          

            return rc;
        }

        public bool GenerateDotBitmap(string inputFileName, string outputFileName)
        {
            bool rc = true;
            OnMessage("Running dot tool - generating bitmap");
            ProcessStartInfo startInfo = new ProcessStartInfo(Application.StartupPath + "/../ThirdParty/Graphviz/bin/dot.exe");
            startInfo.WindowStyle = ProcessWindowStyle.Hidden;
            startInfo.Arguments = "-Tpng " + "\"" + inputFileName + "\"" + " -o " + "\"" + outputFileName + "\"";
            Process proc = Process.Start(startInfo);
            proc.WaitForExit();
            if (proc.ExitCode != 0)
            {
                rc = false;
                OnError("dot: graph image file creation failed.", null);
            }

            return rc;
        }

        public bool GenerateCFG(string code)
        {
            bool rc = true;
            CleanTempDir();
            bool fileRead = false;
            Guid id = Guid.NewGuid();
            string codeFileName = CODE_FILE + "_" + id.ToString();
            OnMessage("Writing temporary code file '" + codeFileName + "'");

            try
            {
                WriteTextFile(codeFileName, code);
                OnMessage("Generating flow points");
                rc = ReadFlowPoints(codeFileName, id);
                if (rc)
                {
                    fileRead = true;
                    OnMessage("loading CFG image");
                    readDotSpec(DOT_LAYOUT_FILE + "_" + id.ToString());
                    OnImageUpdate(DOT_IMAGE_FILE + "_" + id.ToString() + ".png");
                    OnMessage("Cleaning up");
                }
                 File.Delete(DIGRAPH_FILE);
                //File.Delete(m_app.CODE_FILE);
                File.Delete(DOT_LAYOUT_FILE);

                OnMessage("");
            }
            catch (System.Exception ex)
            {
                if (!fileRead)
                {
                }

            }
            string err = CFGParser.GetLastError();
            if (err != "")
            {
                rc = false;
                OnError("Code parsing failed. Check syntax:", err);
            }

            return rc;
        }

        private void WriteTextFile(string filename, string text)
        {
            FileStream fstr = File.OpenWrite(filename);
            using (StreamWriter writer = new StreamWriter(fstr))
            {
                writer.AutoFlush = true;
                writer.Write(text);
                writer.Flush();
                writer.Close();
                writer.Dispose();
            }
            fstr.Close();
            fstr.Dispose();
        }

        private void CleanTempDir()
        {
            try
            {
                Directory.SetCurrentDirectory(Application.StartupPath);
                string[] files = Directory.GetFiles(Application.StartupPath + "\\Temp");
                foreach (string f in files)
                {
                    File.Delete(f);
                }
            }
            catch
            {
            }

            try
            {
                Directory.CreateDirectory("Temp");
            }
            catch
            {
            }
        }

        public VisualFlowPoint FindClosestFlowPoint(Point click, 
                                                    Size originalImageSize, 
                                                    Size sizeOnScreen)
        {
            VisualFlowPoint fp = null;
            int minDistance = 10000000;
            Point closestPoint = new Point(-1, -1);

            float ratioX = ((float)originalImageSize.Width) / ((float)sizeOnScreen.Width);
            float ratioY = ((float)originalImageSize.Height) /((float)sizeOnScreen.Height);
            int xClick = (int)(ratioX * (float)click.X);
            int yClick = (int)(ratioY * (float)(sizeOnScreen.Height - click.Y));
            foreach (Point p in Locations)
            {
                int diffX = p.X-xClick; 
                int diffY = p.Y-yClick;
                int dist =  diffX*diffX + diffY*diffY;
                if (dist < minDistance)
                {
                    minDistance = dist;
                    closestPoint = p;
                }
            }

            if (closestPoint != null)
            {
                if (FlowPoint.ContainsKey(FlowPointName[closestPoint]))
                {
                    fp = FlowPoint[FlowPointName[closestPoint]];
                }
                else
                {
                    fp = new VisualFlowPoint(FlowPointName[closestPoint], FlowPointName[closestPoint]);
                }
            }

            return fp;
        }

        public void TranslateGraphClickToCodeRange(Point click,
                                                   Size originalImageSize, 
                                                   Size sizeOnScreen, 
                                                   out int start, out int count)
        {
            start = 0;
            count = 0;

            VisualFlowPoint fp = FindClosestFlowPoint(click, originalImageSize, sizeOnScreen);
            if (fp != null)
            {
                start = fp.Row;
            }
        }

        public void ApplyCodeColoring(RichTextBox rtbox, string word, Color color)
        {
             int index = -1;
            do
            {
                index = rtbox.Text.IndexOf(word, index + 1);
                if (index >= 0)
                {
                    rtbox.Select(index, word.Length);
                    rtbox.SelectionColor = color;
                }
            }
            while (index >= 0);
        }

        public void ApplyKeywordsColoring(RichTextBox rtbox)
        {
            int loc = rtbox.SelectionStart;
            int len = rtbox.SelectionLength;
            List<string> words = new List<string>();
            words.Add("int");
            words.Add("bool");
            words.Add("if");
            words.Add("else");
            words.Add("for");
            words.Add("while");
            words.Add("do");
            foreach (string word in words)
            {
                ApplyCodeColoring(rtbox, word, Color.Blue);
            }
            rtbox.SelectionStart = loc;
            rtbox.SelectionLength = len;
        }

        public string GraphFileName
        {
            get
            {
                return m_graphFileName;
            }
        }

        public Dictionary<Point, string> FlowPointName;
        public Dictionary<string, VisualFlowPoint> FlowPoint;
        private Size m_ImageSize;
         public string CodeText;
        private string m_graphFileName = null;


        const string OUT_FILE = "temp_cfg";
        public readonly string DIGRAPH_FILE = Application.StartupPath + "\\Temp\\" + OUT_FILE + ".g";
        public readonly string DOT_LAYOUT_FILE = Application.StartupPath + "\\Temp\\" + OUT_FILE + ".dot";
        public readonly string DOT_IMAGE_FILE = Application.StartupPath + "\\Temp\\" + OUT_FILE;
        public readonly string CODE_FILE = Application.StartupPath + "\\Temp\\" + OUT_FILE + ".c";
    }
}
