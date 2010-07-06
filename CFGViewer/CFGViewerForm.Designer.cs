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
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.ButtonZoomIn = new System.Windows.Forms.ToolStripButton();
            this.ButtonZoomOut = new System.Windows.Forms.ToolStripButton();
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
            this.toolStrip1.SuspendLayout();
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
            this.splitContainer1.Panel2.Controls.Add(this.toolStrip1);
            this.splitContainer1.Panel2.Controls.Add(this.panel1);
            this.splitContainer1.Panel2.Controls.Add(this.GraphPanel);
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
            this.GraphPanel.Location = new System.Drawing.Point(0, 26);
            this.GraphPanel.Name = "GraphPanel";
            this.GraphPanel.Size = new System.Drawing.Size(271, 301);
            this.GraphPanel.TabIndex = 0;
            // 
            // toolStrip1
            // 
            this.toolStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.ButtonZoomIn,
            this.ButtonZoomOut});
            this.toolStrip1.Location = new System.Drawing.Point(0, 0);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(271, 27);
            this.toolStrip1.TabIndex = 1;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // ButtonZoomIn
            // 
            this.ButtonZoomIn.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.ButtonZoomIn.Image = ((System.Drawing.Image)(resources.GetObject("ButtonZoomIn.Image")));
            this.ButtonZoomIn.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.ButtonZoomIn.Name = "ButtonZoomIn";
            this.ButtonZoomIn.Size = new System.Drawing.Size(24, 24);
            this.ButtonZoomIn.Text = "Zoom In";
            this.ButtonZoomIn.ToolTipText = "Zoom In";
            this.ButtonZoomIn.Click += new System.EventHandler(this.ButtonZoomIn_Click);
            // 
            // ButtonZoomOut
            // 
            this.ButtonZoomOut.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.ButtonZoomOut.Image = ((System.Drawing.Image)(resources.GetObject("ButtonZoomOut.Image")));
            this.ButtonZoomOut.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.ButtonZoomOut.Name = "ButtonZoomOut";
            this.ButtonZoomOut.Size = new System.Drawing.Size(24, 24);
            this.ButtonZoomOut.Text = "Zoom Out";
            this.ButtonZoomOut.ToolTipText = "Zoom Out";
            this.ButtonZoomOut.Click += new System.EventHandler(this.ButtonZoomOut_Click);
            // 
            // GraphPictureBox
            // 
            this.GraphPictureBox.Location = new System.Drawing.Point(3, 4);
            this.GraphPictureBox.Name = "GraphPictureBox";
            this.GraphPictureBox.Size = new System.Drawing.Size(262, 295);
            this.GraphPictureBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.GraphPictureBox.TabIndex = 0;
            this.GraphPictureBox.TabStop = false;
            this.GraphPictureBox.WaitOnLoad = true;
            this.GraphPictureBox.MouseClick += new System.Windows.Forms.MouseEventHandler(this.GraphPictureBox_MouseClick);
            // 
            // upperToolStrip
            // 
            this.upperToolStrip.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.upperToolStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.OpenFileButton,
            this.editCodeButton,
            this.GenerateCFGButton});
            this.upperToolStrip.Location = new System.Drawing.Point(0, 0);
            this.upperToolStrip.Name = "upperToolStrip";
            this.upperToolStrip.Size = new System.Drawing.Size(571, 27);
            this.upperToolStrip.TabIndex = 2;
            this.upperToolStrip.Text = "Upper Tool Strip";
            // 
            // OpenFileButton
            // 
            this.OpenFileButton.Image = ((System.Drawing.Image)(resources.GetObject("OpenFileButton.Image")));
            this.OpenFileButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.OpenFileButton.Name = "OpenFileButton";
            this.OpenFileButton.Size = new System.Drawing.Size(86, 24);
            this.OpenFileButton.Text = "Open C File";
            this.OpenFileButton.Click += new System.EventHandler(this.OpenFileButton_Click);
            // 
            // editCodeButton
            // 
            this.editCodeButton.CheckOnClick = true;
            this.editCodeButton.Image = ((System.Drawing.Image)(resources.GetObject("editCodeButton.Image")));
            this.editCodeButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.editCodeButton.Name = "editCodeButton";
            this.editCodeButton.Size = new System.Drawing.Size(77, 24);
            this.editCodeButton.Text = "Edit Code";
            this.editCodeButton.ToolTipText = "Enable editing of C Code on left pane";
            this.editCodeButton.Click += new System.EventHandler(this.EditCodeButton_Click);
            // 
            // GenerateCFGButton
            // 
            this.GenerateCFGButton.Image = ((System.Drawing.Image)(resources.GetObject("GenerateCFGButton.Image")));
            this.GenerateCFGButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.GenerateCFGButton.Name = "GenerateCFGButton";
            this.GenerateCFGButton.Size = new System.Drawing.Size(99, 24);
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
            this.splitContainer1.Panel2.PerformLayout();
            this.splitContainer1.ResumeLayout(false);
            this.panel1.ResumeLayout(false);
            this.GraphPanel.ResumeLayout(false);
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
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
        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.ToolStripButton ButtonZoomIn;
        private System.Windows.Forms.ToolStripButton ButtonZoomOut;
    }
}

