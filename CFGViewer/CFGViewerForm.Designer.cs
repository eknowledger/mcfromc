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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CFGViewerForm));
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.codeTextBox = new System.Windows.Forms.TextBox();
            this.panel1 = new System.Windows.Forms.Panel();
            this.CFGProgressBar = new System.Windows.Forms.ProgressBar();
            this.GraphPanel = new System.Windows.Forms.Panel();
            this.GraphPictureBox = new System.Windows.Forms.PictureBox();
            this.upperToolStrip = new System.Windows.Forms.ToolStrip();
            this.OpenFileButton = new System.Windows.Forms.ToolStripButton();
            this.editCodeButton = new System.Windows.Forms.ToolStripButton();
            this.GenerateCFGButton = new System.Windows.Forms.ToolStripButton();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.panel1.SuspendLayout();
            this.GraphPanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.GraphPictureBox)).BeginInit();
            this.upperToolStrip.SuspendLayout();
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
            this.splitContainer1.Panel2.Controls.Add(this.panel1);
            this.splitContainer1.Panel2.Controls.Add(this.GraphPanel);
            this.splitContainer1.Panel2.Paint += new System.Windows.Forms.PaintEventHandler(this.splitContainer1_Panel2_Paint);
            this.splitContainer1.Size = new System.Drawing.Size(547, 354);
            this.splitContainer1.SplitterDistance = 272;
            this.splitContainer1.TabIndex = 1;
            // 
            // codeTextBox
            // 
            this.codeTextBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.codeTextBox.Font = new System.Drawing.Font("Courier New", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.codeTextBox.Location = new System.Drawing.Point(0, 0);
            this.codeTextBox.Multiline = true;
            this.codeTextBox.Name = "codeTextBox";
            this.codeTextBox.ReadOnly = true;
            this.codeTextBox.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.codeTextBox.Size = new System.Drawing.Size(272, 354);
            this.codeTextBox.TabIndex = 0;
            this.codeTextBox.WordWrap = false;
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.CFGProgressBar);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.panel1.Location = new System.Drawing.Point(0, 331);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(271, 23);
            this.panel1.TabIndex = 2;
            // 
            // CFGProgressBar
            // 
            this.CFGProgressBar.BackColor = System.Drawing.SystemColors.HighlightText;
            this.CFGProgressBar.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.CFGProgressBar.ForeColor = System.Drawing.Color.Chartreuse;
            this.CFGProgressBar.Location = new System.Drawing.Point(0, 2);
            this.CFGProgressBar.Name = "CFGProgressBar";
            this.CFGProgressBar.Size = new System.Drawing.Size(271, 21);
            this.CFGProgressBar.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.CFGProgressBar.TabIndex = 5;
            this.CFGProgressBar.Visible = false;
            // 
            // GraphPanel
            // 
            this.GraphPanel.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.GraphPanel.AutoScroll = true;
            this.GraphPanel.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.GraphPanel.Controls.Add(this.GraphPictureBox);
            this.GraphPanel.Location = new System.Drawing.Point(0, 0);
            this.GraphPanel.Name = "GraphPanel";
            this.GraphPanel.Size = new System.Drawing.Size(271, 327);
            this.GraphPanel.TabIndex = 0;
            // 
            // GraphPictureBox
            // 
            this.GraphPictureBox.Location = new System.Drawing.Point(0, 0);
            this.GraphPictureBox.Name = "GraphPictureBox";
            this.GraphPictureBox.Size = new System.Drawing.Size(271, 324);
            this.GraphPictureBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.GraphPictureBox.TabIndex = 0;
            this.GraphPictureBox.TabStop = false;
            this.GraphPictureBox.MouseClick += new System.Windows.Forms.MouseEventHandler(this.GraphPictureBox_MouseClick);
            // 
            // upperToolStrip
            // 
            this.upperToolStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.OpenFileButton,
            this.editCodeButton,
            this.GenerateCFGButton});
            this.upperToolStrip.Location = new System.Drawing.Point(0, 0);
            this.upperToolStrip.Name = "upperToolStrip";
            this.upperToolStrip.Size = new System.Drawing.Size(571, 25);
            this.upperToolStrip.TabIndex = 2;
            this.upperToolStrip.Text = "Upper Tool Strip";
            // 
            // OpenFileButton
            // 
            this.OpenFileButton.Image = ((System.Drawing.Image)(resources.GetObject("OpenFileButton.Image")));
            this.OpenFileButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.OpenFileButton.Name = "OpenFileButton";
            this.OpenFileButton.Size = new System.Drawing.Size(82, 22);
            this.OpenFileButton.Text = "Open C File";
            this.OpenFileButton.Click += new System.EventHandler(this.OpenFileButton_Click);
            // 
            // editCodeButton
            // 
            this.editCodeButton.CheckOnClick = true;
            this.editCodeButton.Image = ((System.Drawing.Image)(resources.GetObject("editCodeButton.Image")));
            this.editCodeButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.editCodeButton.Name = "editCodeButton";
            this.editCodeButton.Size = new System.Drawing.Size(73, 22);
            this.editCodeButton.Text = "Edit Code";
            this.editCodeButton.ToolTipText = "Enable editing of C Code on left pane";
            this.editCodeButton.Click += new System.EventHandler(this.EditCodeButton_Click);
            // 
            // GenerateCFGButton
            // 
            this.GenerateCFGButton.Image = ((System.Drawing.Image)(resources.GetObject("GenerateCFGButton.Image")));
            this.GenerateCFGButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.GenerateCFGButton.Name = "GenerateCFGButton";
            this.GenerateCFGButton.Size = new System.Drawing.Size(95, 22);
            this.GenerateCFGButton.Text = "Generate CFG";
            this.GenerateCFGButton.Click += new System.EventHandler(this.GenerateCFGButton_Click);
            // 
            // CFGViewerForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(571, 418);
            this.Controls.Add(this.upperToolStrip);
            this.Controls.Add(this.splitContainer1);
            this.Name = "CFGViewerForm";
            this.ShowIcon = false;
            this.Text = "Control Flow Graph Viewer";
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel1.PerformLayout();
            this.splitContainer1.Panel2.ResumeLayout(false);
            this.splitContainer1.ResumeLayout(false);
            this.panel1.ResumeLayout(false);
            this.GraphPanel.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.GraphPictureBox)).EndInit();
            this.upperToolStrip.ResumeLayout(false);
            this.upperToolStrip.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.TextBox codeTextBox;
        private System.Windows.Forms.Panel GraphPanel;
        private System.Windows.Forms.PictureBox GraphPictureBox;
        private System.Windows.Forms.ToolStrip upperToolStrip;
        private System.Windows.Forms.ToolStripButton OpenFileButton;
        private System.Windows.Forms.ToolStripButton editCodeButton;
        private System.Windows.Forms.ToolStripButton GenerateCFGButton;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.ProgressBar CFGProgressBar;
    }
}

