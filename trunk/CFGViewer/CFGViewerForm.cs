using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace CFGViewer
{
    public partial class CFGViewerForm : Form
    {
        public CFGViewerForm()
        {
            InitializeComponent();
            GraphPictureBox.Image = Image.FromFile("Untitled1.png");
            m_app = new CFGViewerApp();
            m_app.readDotSpec("out.dot");
        }

        private void GraphPictureBox_MouseClick(object sender, MouseEventArgs e)
        {
            int minDistance = 10000000;
            Point closestPoint = new Point(-1,-1);
            Point imgSize = new Point(GraphPictureBox.Image.Size);
            Point cntrlSize = new Point(GraphPictureBox.Size);

            int xClick = (int)( ( ((float)e.X) / ((float)cntrlSize.X) ) * ((float)imgSize.X));
            int yClick = (int)((((float)(cntrlSize.Y - e.Y)) / ((float)cntrlSize.Y)) * ((float)imgSize.Y));

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
                codeTextBox.Text = m_app.FlowPointName[closestPoint];
            }
        }

        private CFGViewerApp m_app;
    }
}
