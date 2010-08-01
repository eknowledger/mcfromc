using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace CFGViewer
{
    public partial class MCGraphViewerForm : Form
    {
        public MCGraphViewerForm(string graphName, CFGViewerApp app)
        {
            InitializeComponent();
            m_app = app;
            if (graphName != null)
                labelGraphName.Text = graphName;
            else labelGraphName.Text = "";
            string fname = m_app.DIGRAPH_FILE + ".MC_" + graphName;
            Guid id = Guid.NewGuid();
            if (m_app.GenerateDotBitmap(fname, fname + id.ToString() + ".png"))
            {
                MCGraphPictureBox.Image = new Bitmap(fname + id.ToString() + ".png");
                Size imgSize = MCGraphPictureBox.Image.Size;
                this.Size = new Size(imgSize.Width + 37, imgSize.Height + 116);
            }
        }

        private void buttonClose_Click(object sender, EventArgs e)
        {
            Close();
        }

        CFGViewerApp m_app;
    }
}
