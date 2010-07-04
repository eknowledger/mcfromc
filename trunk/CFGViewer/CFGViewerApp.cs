using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Drawing;
using ParserDotNetBridge;
using System.Collections;

namespace CFGViewer
{
    class CFGViewerApp
    {
        public string readFlowPoints(string filename)
        {
            CodeText = null;
            ArrayList arr = null;
            FlowPoint = new Dictionary<string, VisualFlowPoint>();
            arr = CFGParser.GenerateCFG(filename);

            if (arr != null)
            {
                foreach (VisualFlowPoint fp in arr)
                {
                    FlowPoint[fp.Name] = fp;
                }
            }

            using (StreamReader reader = new StreamReader(filename))
            {
                CodeText = reader.ReadToEnd();
            }

            return CodeText;
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

        public Dictionary<Point, string> FlowPointName;
        public Dictionary<string, VisualFlowPoint> FlowPoint;
        private int m_Height;
        private int m_Width;
        public string CodeText;
    }
}
