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
            //int start, count;
            //m_app.TranslateGraphClickToCodeRange(e.Location,
            //                    GraphPictureBox.Image.Size,
            //                    GraphPictureBox.Size,
            //                    out start, out count);

            ////codeTextBox.Lines = lines;
            ////int index = m_app.findOpeningParentheses(codeTextBox.Text, charStart);
            //codeTextBox.SelectionStart = start;
            //codeTextBox.SelectionLength = count;
          }

        private CFGViewerApp m_app;

        private void SetMessage(string text)
        {
            CFGProgressBar.Value += 10;
            SetMessageWithNoProgress(text, false);
        }

        private void SetMessageWithNoProgress(string text, bool clearBgd)
        {
            Graphics g = CFGProgressBar.CreateGraphics(); 
            if (clearBgd)
                g.Clear(Color.White);
            g.DrawString(
                text,
                new Font("Arial", (float)8.25, FontStyle.Regular),
                Brushes.Black,
                new PointF(CFGProgressBar.Width / 8 - 10, CFGProgressBar.Height / 2 - 7));
        }

        private void LoadImageFromFile(string imageFile)
        {
            GraphPictureBox.Image = new Bitmap(imageFile);
            GraphPictureBox.Size = m_app.ImageSize;
            GraphPictureBox.Refresh();
        }

        private void OnError(string heading, string err)
        {
            if (err != null)
            {
                ErrorMessageDialog dlg = new ErrorMessageDialog("Code Parsing Failed", heading, err);
                dlg.ShowDialog(this);
            }
            else
            {
                MessageBox.Show(this, heading, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
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
            
            CFGProgressBar.Value = 0;
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

        private void GraphPictureBox_MouseMove(object sender, MouseEventArgs e)
        {
            if (GraphPictureBox.Image != null)
            {
                //Point p = GraphPictureBox.PointToClient(e.Location);
                VisualFlowPoint fp = m_app.FindClosestFlowPoint(e.Location,
                                    m_app.ImageSize,
                                    GraphPictureBox.Size);
                if (fp != null && fp != m_oldFP)
                {
                    SetMessageWithNoProgress(fp.Text,true);
                    m_oldFP = fp;
                }
            }
        }

        private VisualFlowPoint m_oldFP = null;
    }
}
