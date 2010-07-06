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
                        //int index = m_app.findOpeningParentheses(codeTextBox.Text, charStart);
                        codeTextBox.SelectionStart = charStart;
                        codeTextBox.SelectionLength = charCount;
                    }
                }
            }
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

        private void UpdateImageSize()
        {
            GraphPictureBox.Size = new Size(m_app.ImageWidth, m_app.ImageHeight);
            GraphPictureBox.Refresh();
        }

        private void LoadImageFromFile()
        {
            GraphPictureBox.Load(m_app.DOT_IMAGE_FILE);
            GraphPictureBox.Size = new Size(m_app.ImageWidth, m_app.ImageHeight);
            GraphPictureBox.Refresh();
            //GraphPictureBox.Image = Image.FromFile(m_app.DOT_IMAGE_FILE);
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
