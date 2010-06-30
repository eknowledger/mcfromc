using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Drawing;

namespace CFGViewer
{
    class CFGViewerApp
    {
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
                            line.Trim();
                            string fpName = line.Substring(0, line.IndexOf(' '));
                            FlowPointName.Add(new Point(x, y), fpName);
                        }
                    }
                }
            }
        }

        public List<Point> Locations
        {
            get
            {
                return FlowPointName.Keys.ToList<Point>();
            }
        }

        public Dictionary<Point, string> FlowPointName;
    }
}
