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
        public ErrorMessageDialog(string caption, string heading, string code)
        {
            InitializeComponent();
            if (caption != null)
                this.Text = caption;
            if (heading != null)
                labelHeading.Text = heading;
            if (code != null)
            {
                richTextBoxCode.Text = code;
                int startIndex = richTextBoxCode.Text.LastIndexOf('^');
                int lastIndex = richTextBoxCode.Text.Length-1;
                richTextBoxCode.Select(startIndex, lastIndex - startIndex + 1);
                richTextBoxCode.SelectionColor = Color.Red;
                richTextBoxCode.Select(0, 0);
                ApplyKeywordsColoring();
                richTextBoxCode.BackColor = Color.White;
            }
        }

        private void buttonOk_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void ApplyCodeColoring(string word, Color color)
        {
            int index = -1;
            do 
            {
                index = richTextBoxCode.Text.IndexOf(word, index+1);
                if (index >= 0)
                {
                    richTextBoxCode.Select(index, word.Length);
                    richTextBoxCode.SelectionColor = color;
                }
            } 
            while (index >= 0);
        }

        private void ApplyKeywordsColoring()
        {
            List<string> words = new List<string>();
            words.Add("int");
            words.Add("bool");
            words.Add("if");
            words.Add("else");
            words.Add("for");
            words.Add("while");
            words.Add("do");
            foreach (string word in words)
            {
                ApplyCodeColoring(word, Color.Blue);
            }
            richTextBoxCode.Select(0, 0);
        }
    }
}
