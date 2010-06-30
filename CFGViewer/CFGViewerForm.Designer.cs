namespace CFGViewer
{
    partial class CFGViewerForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.codeTextBox = new System.Windows.Forms.TextBox();
            this.GraphPanel = new System.Windows.Forms.Panel();
            this.GraphPictureBox = new System.Windows.Forms.PictureBox();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.GraphPanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.GraphPictureBox)).BeginInit();
            this.SuspendLayout();
            // 
            // splitContainer1
            // 
            this.splitContainer1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.splitContainer1.Location = new System.Drawing.Point(12, 30);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.codeTextBox);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.GraphPanel);
            this.splitContainer1.Size = new System.Drawing.Size(547, 379);
            this.splitContainer1.SplitterDistance = 272;
            this.splitContainer1.TabIndex = 1;
            // 
            // codeTextBox
            // 
            this.codeTextBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.codeTextBox.Location = new System.Drawing.Point(0, 0);
            this.codeTextBox.Multiline = true;
            this.codeTextBox.Name = "codeTextBox";
            this.codeTextBox.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.codeTextBox.Size = new System.Drawing.Size(272, 379);
            this.codeTextBox.TabIndex = 0;
            this.codeTextBox.WordWrap = false;
            // 
            // GraphPanel
            // 
            this.GraphPanel.AutoScroll = true;
            this.GraphPanel.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.GraphPanel.Controls.Add(this.GraphPictureBox);
            this.GraphPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.GraphPanel.Location = new System.Drawing.Point(0, 0);
            this.GraphPanel.Name = "GraphPanel";
            this.GraphPanel.Size = new System.Drawing.Size(271, 379);
            this.GraphPanel.TabIndex = 0;
            // 
            // GraphPictureBox
            // 
            this.GraphPictureBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.GraphPictureBox.Location = new System.Drawing.Point(0, 0);
            this.GraphPictureBox.Name = "GraphPictureBox";
            this.GraphPictureBox.Size = new System.Drawing.Size(271, 379);
            this.GraphPictureBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.GraphPictureBox.TabIndex = 0;
            this.GraphPictureBox.TabStop = false;
            this.GraphPictureBox.MouseClick += new System.Windows.Forms.MouseEventHandler(this.GraphPictureBox_MouseClick);
            // 
            // CFGViewerForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(571, 418);
            this.Controls.Add(this.splitContainer1);
            this.Name = "CFGViewerForm";
            this.ShowIcon = false;
            this.Text = "Control Flow Graph Viewer";
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel1.PerformLayout();
            this.splitContainer1.Panel2.ResumeLayout(false);
            this.splitContainer1.ResumeLayout(false);
            this.GraphPanel.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.GraphPictureBox)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.TextBox codeTextBox;
        private System.Windows.Forms.Panel GraphPanel;
        private System.Windows.Forms.PictureBox GraphPictureBox;
    }
}

