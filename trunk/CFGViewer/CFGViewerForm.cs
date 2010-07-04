using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using ParserDotNetBridge;

namespace CFGViewer
{
    public partial class CFGViewerForm : Form
    {
        public CFGViewerForm()
        {
            InitializeComponent();
            GraphPictureBox.Image = Image.FromFile("Untitled1.png");
            m_app = new CFGViewerApp();
            codeTextBox.Text = m_app.readFlowPoints("test2.c");
            m_app.readDotSpec("out.dot");
            GraphPictureBox.Size = new Size(m_app.ImageWidth, m_app.ImageHeight);
        }

        private void GraphPictureBox_MouseClick(object sender, MouseEventArgs e)
        {
            int minDistance = 10000000;
            Point closestPoint = new Point(-1,-1);
            Point imgSize = new Point(GraphPictureBox.Image.Size);
            Point cntrlSize = new Point(GraphPictureBox.Size);

            int xClick = e.X;
            int yClick = cntrlSize.Y - e.Y;
            foreach (Point p in m_app.Locations)
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

            if (closestPoint != null) {
                if (m_app.FlowPoint.ContainsKey(m_app.FlowPointName[closestPoint]))
                {
                    VisualFlowPoint fp = m_app.FlowPoint[m_app.FlowPointName[closestPoint]];
                    if (fp != null)
                    {
                        int rowNum = 0;
                        int charCount = 0;
                        int charStart = 0;
                        for (int i = 0; i < codeTextBox.Lines.Length; i++)
                        {
                            if (i == fp.Row)
                            {
                                charStart = charCount;
                                charCount = codeTextBox.Lines[i].Length;  
                                break;
                            }

                            charCount+=codeTextBox.Lines[i].Length + 2;

                        }

                        //codeTextBox.Lines = lines;
                        int index = m_app.findOpeningParentheses(codeTextBox.Text, charStart);
                        codeTextBox.SelectionStart = charStart;
                        codeTextBox.SelectionLength = 0;
                    }
                }
            }
        }

        private CFGViewerApp m_app;
    }
}
