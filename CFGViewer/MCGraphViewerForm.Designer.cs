namespace CFGViewer
{
    partial class MCGraphViewerForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MCGraphViewerForm));
            this.panelMain = new System.Windows.Forms.Panel();
            this.MCGraphPictureBox = new System.Windows.Forms.PictureBox();
            this.buttonClose = new System.Windows.Forms.Button();
            this.labelGraphName = new System.Windows.Forms.Label();
            this.panelMain.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.MCGraphPictureBox)).BeginInit();
            this.SuspendLayout();
            // 
            // panelMain
            // 
            this.panelMain.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.panelMain.AutoScroll = true;
            this.panelMain.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.panelMain.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelMain.Controls.Add(this.MCGraphPictureBox);
            this.panelMain.Location = new System.Drawing.Point(12, 37);
            this.panelMain.Name = "panelMain";
            this.panelMain.Size = new System.Drawing.Size(259, 265);
            this.panelMain.TabIndex = 0;
            // 
            // MCGraphPictureBox
            // 
            this.MCGraphPictureBox.InitialImage = null;
            this.MCGraphPictureBox.Location = new System.Drawing.Point(3, 3);
            this.MCGraphPictureBox.Name = "MCGraphPictureBox";
            this.MCGraphPictureBox.Size = new System.Drawing.Size(945, 878);
            this.MCGraphPictureBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.MCGraphPictureBox.TabIndex = 0;
            this.MCGraphPictureBox.TabStop = false;
            // 
            // buttonClose
            // 
            this.buttonClose.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.buttonClose.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.buttonClose.Location = new System.Drawing.Point(104, 313);
            this.buttonClose.Name = "buttonClose";
            this.buttonClose.Size = new System.Drawing.Size(75, 23);
            this.buttonClose.TabIndex = 1;
            this.buttonClose.Text = "Close";
            this.buttonClose.UseVisualStyleBackColor = true;
            this.buttonClose.Click += new System.EventHandler(this.buttonClose_Click);
            // 
            // labelGraphName
            // 
            this.labelGraphName.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.labelGraphName.AutoSize = true;
            this.labelGraphName.Font = new System.Drawing.Font("Tahoma", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(177)));
            this.labelGraphName.Location = new System.Drawing.Point(100, 9);
            this.labelGraphName.Name = "labelGraphName";
            this.labelGraphName.Size = new System.Drawing.Size(62, 24);
            this.labelGraphName.TabIndex = 2;
            this.labelGraphName.Text = "Name";
            this.labelGraphName.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // MCGraphViewerForm
            // 
            this.AcceptButton = this.buttonClose;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.buttonClose;
            this.ClientSize = new System.Drawing.Size(283, 348);
            this.Controls.Add(this.labelGraphName);
            this.Controls.Add(this.buttonClose);
            this.Controls.Add(this.panelMain);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MinimumSize = new System.Drawing.Size(200, 375);
            this.Name = "MCGraphViewerForm";
            this.ShowIcon = false;
            this.ShowInTaskbar = false;
            this.Text = "Monotonicity Constraints Graph Viewer";
            this.panelMain.ResumeLayout(false);
            this.panelMain.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.MCGraphPictureBox)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Panel panelMain;
        private System.Windows.Forms.Button buttonClose;
        private System.Windows.Forms.PictureBox MCGraphPictureBox;
        private System.Windows.Forms.Label labelGraphName;
    }
}