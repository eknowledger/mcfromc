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
            m_app = new CFGViewerApp(SetMessage);
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

        private void SetMessage(string text)
        {
            CFGProgressBar.Value += 10;
            CFGProgressBar.CreateGraphics().DrawString(
                text, 
                new Font("Arial", (float)8.25, FontStyle.Regular), 
                Brushes.Black, 
                new PointF(CFGProgressBar.Width / 8 - 10, CFGProgressBar.Height / 2 - 7));
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
            try
            {
                Directory.SetCurrentDirectory(Application.StartupPath);
                string[] files = Directory.GetFiles(Application.StartupPath + "\\Temp");
                foreach(string f in files)
                {
                    File.Delete(f);
                }
            }
            catch
            {
            }

            try
            {
                Directory.CreateDirectory("Temp");
            }
            catch
            {
            }

            bool fileRead = false;
            if (GraphPictureBox.Image != null) {
                GraphPictureBox.Image = null;
            }
            CFGProgressBar.Show();
            CFGProgressBar.Value = 0;
            Guid id = Guid.NewGuid();
            string codeFileName =  m_app.CODE_FILE +  "_" + id.ToString();
            SetMessage("Writing temporary code file '" + codeFileName + "'");
            try
            {

                FileStream fstr = File.OpenWrite(codeFileName);
                using (StreamWriter writer = new StreamWriter(fstr))
                {
                    writer.AutoFlush = true;
                    writer.Write(codeTextBox.Text);
                    writer.Flush();
                    writer.Close();
                    writer.Dispose();
                }
                fstr.Close();
                fstr.Dispose();

                SetMessage("Generating flow points");
                m_app.readFlowPoints(codeFileName);
                fileRead = true;
                SetMessage("loading CFG image");
                GraphPictureBox.Load(m_app.DOT_IMAGE_FILE);
               // GraphPictureBox.Image = Image.FromFile(m_app.DOT_IMAGE_FILE);
                m_app.readDotSpec(m_app.DOT_LAYOUT_FILE);
                GraphPictureBox.Size = new Size(m_app.ImageWidth, m_app.ImageHeight);
                GraphPictureBox.Refresh();
                SetMessage("Cleaning up");
               
                File.Delete(m_app.DIGRAPH_FILE);
                //File.Delete(m_app.CODE_FILE);
                File.Delete(m_app.DOT_LAYOUT_FILE);
                
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

        private void splitContainer1_Panel2_Paint(object sender, PaintEventArgs e)
        {

        }
    }
}
