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

namespace CFGViewer
{
    public delegate void DelegateMessage(string message);

    class CFGViewerApp
    {
        public CFGViewerApp(DelegateMessage msgDelegator)
        {
            OnMessage += msgDelegator;
        }

        public event DelegateMessage OnMessage;

        public void readFlowPoints(string filename)
        {
            ArrayList arr = null;
            FlowPoint = new Dictionary<string, VisualFlowPoint>();
            string graphText = null;
            arr = CFGParser.GenerateCFG(filename, out graphText);

            if (arr != null)
            {
                foreach (VisualFlowPoint fp in arr)
                {
                    FlowPoint[fp.Name] = fp;
                }
            }

            if (graphText != null)
            {
                WriteGraphToFile(graphText);
                RunDot();
            }
        }

        public void readDotSpec(string filename)
        {
            FlowPointName = new Dictionary<Point, string>();
            StreamReader reader = new StreamReader(filename);
            while (!reader.EndOfStream)
            {
                string line = reader.ReadLine();
                if (line.IndexOf("->") < 0)
                {
                    int posInd = line.IndexOf("pos");
                    if (posInd >= 0)
                    {
                        posInd += 5;
                        int nextInd = line.IndexOf(',', posInd);
                        string numStr = line.Substring(posInd, nextInd - posInd);
                        int x = -1, y = -1;
                        int.TryParse(numStr, out x);
                        posInd = nextInd + 1;
                        nextInd = line.IndexOf('\"', posInd);
                        numStr = line.Substring(posInd, nextInd - posInd);
                        int.TryParse(numStr, out y);
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
                        int.TryParse(widthStr, out m_Width);
                        int.TryParse(heightStr, out m_Height);
                    }
                }
            }
            reader.Close();
            reader.Dispose();
        }

        public int ImageHeight
        {
            get{
                return m_Height;
            }
        }
        public int ImageWidth
        {
            get {
                return m_Width;
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

        private void WriteGraphToFile(string graphText)
        {
            OnMessage("Writing graph to file");
            FileStream fstr = File.OpenWrite(DIGRAPH_FILE);
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

        private void RunDot()
        {
            OnMessage("Running dot tool - generating layout");
            ProcessStartInfo startInfo = new ProcessStartInfo("../ThirdParty/Graphviz/bin/dot.exe");
            startInfo.WindowStyle = ProcessWindowStyle.Hidden;
            startInfo.Arguments = "-Tdot " + DIGRAPH_FILE + " -o " + DOT_LAYOUT_FILE;
            Process p1 = Process.Start(startInfo);
            OnMessage("Running dot tool - generating bitmap");
            startInfo.Arguments = "-Tgif " + DIGRAPH_FILE + " -o " + DOT_IMAGE_FILE;
            Process p2 = Process.Start(startInfo);

            p1.WaitForExit();
            p2.WaitForExit();
        }

        public Dictionary<Point, string> FlowPointName;
        public Dictionary<string, VisualFlowPoint> FlowPoint;
        private int m_Height;
        private int m_Width;
        public string CodeText;

        const string OUT_FILE = "temp_cfg";
        public readonly string DIGRAPH_FILE = Application.StartupPath + "\\Temp\\" + OUT_FILE + ".g";
        public readonly string DOT_LAYOUT_FILE = Application.StartupPath + "\\Temp\\" + OUT_FILE + ".dot";
        public readonly string DOT_IMAGE_FILE = Application.StartupPath + "\\Temp\\" + OUT_FILE + ".gif";
        public readonly string CODE_FILE = Application.StartupPath + "\\Temp\\" + OUT_FILE + ".c";
    }
}
