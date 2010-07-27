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
    public partial class ErrorMessageDialog : Form
    {
        public ErrorMessageDialog(string caption, string heading, string code, CFGViewerApp app)
        {
            InitializeComponent();
            m_app = app;
            if (caption != null)
                this.Text = caption;
            if (heading != null)
                labelHeading.Text = heading;
            if (code != null)
            {
                richTextBoxCode.Text = code;
                int startIndex = richTextBoxCode.Text.LastIndexOf('^');
                if (startIndex > 0)
                {
                    int lastIndex = richTextBoxCode.Text.Length - 1;
                    richTextBoxCode.Select(startIndex, lastIndex - startIndex + 1);
                    richTextBoxCode.SelectionColor = Color.Red;
                    richTextBoxCode.Select(0, 0);
                }
                m_app.ApplyKeywordsColoring(richTextBoxCode);
                richTextBoxCode.BackColor = Color.White;
            }
        }

        private void buttonOk_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private CFGViewerApp m_app;
     }
}
