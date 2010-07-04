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
            //GraphPictureBox.Image = Image.FromFile("Untitled1.png");
            m_app = new CFGViewerApp();
            //codeTextBox.Text = m_app.readFlowPoints("test2.c");
            //m_app.readDotSpec("out.dot");
            //GraphPictureBox.Size = new Size(m_app.ImageWidth, m_app.ImageHeight);
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
        private const string TEMP_C_FILE_PATH = "temp.c";

        private void SetMessage(string text)
        {
            CFGProgressBar.CreateGraphics().DrawString(
                text, 
                new Font("Arial", (float)8.25, FontStyle.Regular), 
                Brushes.Black, 
                new PointF(CFGProgressBar.Width / 8 - 10, CFGProgressBar.Height / 2 - 7));
            Thread.Sleep(200);
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
                codeTextBox.Text = m_app.readFlowPoints(dlg.FileName);
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
            bool fileRead = false;
            CFGProgressBar.Show();
            CFGProgressBar.Value = 0;
            CFGProgressBar.Value += 15;
            SetMessage("Writing temporary code file '" + TEMP_C_FILE_PATH + "'");
            try
            {        
                using (StreamWriter writer = new StreamWriter(TEMP_C_FILE_PATH, false)) {
                    writer.Write(codeTextBox.Text);
                    writer.Flush();
                    writer.Close();
                }
                CFGProgressBar.Value += 15;
                //SetMessage("Finished writing temporary code file '" + TEMP_C_FILE_PATH + "'");
                SetMessage("Generating flow points");
                m_app.readFlowPoints(TEMP_C_FILE_PATH);
                CFGProgressBar.Value += 40;
                //SetMessage("Finished generating flow points");
                fileRead = true;
                SetMessage("Cleaning up");
                 File.Delete(TEMP_C_FILE_PATH);
                CFGProgressBar.Value += 30;
                SetMessage("");
            }
            catch (System.Exception ex)
            {
                if (!fileRead)
                {
                }
            	
            }
            CFGProgressBar.Value += 10;
            CFGProgressBar.Hide();
        }
    }
}
