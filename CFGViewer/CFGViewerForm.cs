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
using System.Threading;


namespace CFGViewer
{

    public partial class CFGViewerForm : Form
    {
        public CFGViewerForm()
        {
            InitializeComponent();
            codeTextBox.BackColor = Color.White;
            codeTextBox.ForeColor = codeTextBox.ReadOnly ? Color.Gray : Color.Black;
            m_app = new CFGViewerApp(SetMessage, LoadImageFromFile, OnError);
        }

        private void GraphPictureBox_MouseClick(object sender, MouseEventArgs e)
        {
            int start, count;
            m_app.TranslateGraphClickToCodeRange(e.Location,
                                GraphPictureBox.Image.Size,
                                GraphPictureBox.Size,
                                out start, out count);

            //codeTextBox.Lines = lines;
            //int index = m_app.findOpeningParentheses(codeTextBox.Text, charStart);
            codeTextBox.SelectionStart = start;
            codeTextBox.SelectionLength = count;
          }

        private CFGViewerApp m_app;

        private void SetMessage(string text)
        {
            CFGProgressBar.Value += 10;
            CFGProgressBar.CreateGraphics().DrawString(
                text, 
                new Font("Arial", (float)8.25, FontStyle.Regular), 
                Brushes.Black, 
                new PointF(CFGProgressBar.Width / 8 - 10, CFGProgressBar.Height / 2 - 7));
        }

        private void LoadImageFromFile()
        {
            GraphPictureBox.Image = new Bitmap(m_app.DOT_IMAGE_FILE);
            GraphPictureBox.Size = new Size(m_app.ImageWidth, m_app.ImageHeight);
            GraphPictureBox.Refresh();
        }

        private void OnError(string err)
        {
            MessageBox.Show(this, err, "", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
        }

        private void OpenFileButton_Click(object sender, EventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Multiselect = false;
            dlg.Filter = ".c files|*.c|All files|*.*";
            DialogResult res = dlg.ShowDialog(this);
            if (res == DialogResult.OK) 
            {
                this.Text = "Control Flow Graph Viewer" + " - " + dlg.FileName;
                
                using (StreamReader reader = new StreamReader(dlg.FileName))
                {
                    codeTextBox.Text = reader.ReadToEnd();
                    m_app.CodeText = codeTextBox.Text;
                }
            }     
        }

        private void EditCodeButton_Click(object sender, EventArgs e)
        {
            codeTextBox.ReadOnly = !codeTextBox.ReadOnly;
            codeTextBox.BackColor = Color.White;
            codeTextBox.ForeColor = codeTextBox.ReadOnly ? Color.Gray : Color.Black;
        }



        private void GenerateCFGButton_Click(object sender, EventArgs e)
        {
  
            if (GraphPictureBox.Image != null) {
                GraphPictureBox.Image = null;
            }
            CFGProgressBar.Value = 0;
            CFGProgressBar.Show();

            m_app.GenerateCFG(codeTextBox.Text);
            
            CFGProgressBar.Value += 10;
            CFGProgressBar.Hide();
        }

        private void ButtonZoomIn_Click(object sender, EventArgs e)
        {
            Size size = new Size();
            size.Width = (int)(((float)GraphPictureBox.Size.Width) * 1.3);
            size.Height = (int)(((float)GraphPictureBox.Size.Height) * 1.3);
            GraphPictureBox.Size = size;
        }

        private void ButtonZoomOut_Click(object sender, EventArgs e)
        {
            Size size = new Size();
            size.Width = (int)(((float)GraphPictureBox.Size.Width) / 1.3);
            size.Height = (int)(((float)GraphPictureBox.Size.Height) / 1.3);
            GraphPictureBox.Size = size;
        }
    }
}
