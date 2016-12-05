namespace Example
{
    partial class form1
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
            this.menuStrip = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.newToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator = new System.Windows.Forms.ToolStripSeparator();
            this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveAsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.sidePanel = new System.Windows.Forms.Panel();
            this.currentWaveSelector = new System.Windows.Forms.NumericUpDown();
            this.currentWaveLabel = new System.Windows.Forms.Label();
            this.mapLabel = new System.Windows.Forms.Label();
            this.addObjectsLabel = new System.Windows.Forms.Label();
            this.descriptionLabel = new System.Windows.Forms.Label();
            this.selectedLabel = new System.Windows.Forms.Label();
            this.addShipButton = new System.Windows.Forms.Button();
            this.addPlanetButton = new System.Windows.Forms.Button();
            this.shipPanel = new System.Windows.Forms.Panel();
            this.shipPilot = new System.Windows.Forms.ComboBox();
            this.shipPilotLabel = new System.Windows.Forms.Label();
            this.shipTypeLabel = new System.Windows.Forms.Label();
            this.shipType = new System.Windows.Forms.ComboBox();
            this.shipDeleteButton = new System.Windows.Forms.Button();
            this.shipWaveLabel = new System.Windows.Forms.Label();
            this.shipWave = new System.Windows.Forms.NumericUpDown();
            this.shipPositionLabel = new System.Windows.Forms.Label();
            this.shipPosX = new System.Windows.Forms.TextBox();
            this.shipPosY = new System.Windows.Forms.TextBox();
            this.shipPosZ = new System.Windows.Forms.TextBox();
            this.planetPanel = new System.Windows.Forms.Panel();
            this.planetScaleLabel = new System.Windows.Forms.Label();
            this.planetScale = new System.Windows.Forms.TextBox();
            this.planetDeleteButton = new System.Windows.Forms.Button();
            this.planetPosZ = new System.Windows.Forms.MaskedTextBox();
            this.planetPosY = new System.Windows.Forms.MaskedTextBox();
            this.planetPosX = new System.Windows.Forms.MaskedTextBox();
            this.planetPositionLabel = new System.Windows.Forms.Label();
            this.planetSolid = new System.Windows.Forms.CheckBox();
            this.planetTextureLabel = new System.Windows.Forms.Label();
            this.planetTexture = new System.Windows.Forms.ComboBox();
            this.RenderBox = new System.Windows.Forms.Panel();
            this.statusStrip = new System.Windows.Forms.StatusStrip();
            this.menuStrip.SuspendLayout();
            this.sidePanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.currentWaveSelector)).BeginInit();
            this.shipPanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.shipWave)).BeginInit();
            this.planetPanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip
            // 
            this.menuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem});
            this.menuStrip.Location = new System.Drawing.Point(0, 0);
            this.menuStrip.Name = "menuStrip";
            this.menuStrip.Size = new System.Drawing.Size(1904, 24);
            this.menuStrip.TabIndex = 0;
            this.menuStrip.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newToolStripMenuItem,
            this.openToolStripMenuItem,
            this.toolStripSeparator,
            this.saveToolStripMenuItem,
            this.saveAsToolStripMenuItem,
            this.toolStripSeparator2,
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "&File";
            // 
            // newToolStripMenuItem
            // 
            this.newToolStripMenuItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.newToolStripMenuItem.Name = "newToolStripMenuItem";
            this.newToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.N)));
            this.newToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.newToolStripMenuItem.Text = "&New";
            this.newToolStripMenuItem.Click += new System.EventHandler(this.newToolStripMenuItem_Click);
            // 
            // openToolStripMenuItem
            // 
            this.openToolStripMenuItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.openToolStripMenuItem.Name = "openToolStripMenuItem";
            this.openToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.O)));
            this.openToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.openToolStripMenuItem.Text = "&Open";
            this.openToolStripMenuItem.Click += new System.EventHandler(this.openToolStripMenuItem_Click);
            // 
            // toolStripSeparator
            // 
            this.toolStripSeparator.Name = "toolStripSeparator";
            this.toolStripSeparator.Size = new System.Drawing.Size(149, 6);
            // 
            // saveToolStripMenuItem
            // 
            this.saveToolStripMenuItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
            this.saveToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.S)));
            this.saveToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.saveToolStripMenuItem.Text = "&Save";
            this.saveToolStripMenuItem.Click += new System.EventHandler(this.saveToolStripMenuItem_Click);
            // 
            // saveAsToolStripMenuItem
            // 
            this.saveAsToolStripMenuItem.Name = "saveAsToolStripMenuItem";
            this.saveAsToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.saveAsToolStripMenuItem.Text = "Save &As";
            this.saveAsToolStripMenuItem.Click += new System.EventHandler(this.saveAsToolStripMenuItem_Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(149, 6);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.exitToolStripMenuItem.Text = "E&xit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // sidePanel
            // 
            this.sidePanel.Controls.Add(this.currentWaveSelector);
            this.sidePanel.Controls.Add(this.currentWaveLabel);
            this.sidePanel.Controls.Add(this.mapLabel);
            this.sidePanel.Controls.Add(this.addObjectsLabel);
            this.sidePanel.Controls.Add(this.descriptionLabel);
            this.sidePanel.Controls.Add(this.selectedLabel);
            this.sidePanel.Controls.Add(this.addShipButton);
            this.sidePanel.Controls.Add(this.addPlanetButton);
            this.sidePanel.Dock = System.Windows.Forms.DockStyle.Right;
            this.sidePanel.Location = new System.Drawing.Point(1747, 24);
            this.sidePanel.Name = "sidePanel";
            this.sidePanel.Size = new System.Drawing.Size(157, 1018);
            this.sidePanel.TabIndex = 1;
            // 
            // currentWaveSelector
            // 
            this.currentWaveSelector.Location = new System.Drawing.Point(82, 105);
            this.currentWaveSelector.Name = "currentWaveSelector";
            this.currentWaveSelector.Size = new System.Drawing.Size(50, 20);
            this.currentWaveSelector.TabIndex = 13;
            this.currentWaveSelector.ValueChanged += new System.EventHandler(this.numericUpDown1_ValueChanged);
            // 
            // currentWaveLabel
            // 
            this.currentWaveLabel.AutoSize = true;
            this.currentWaveLabel.Location = new System.Drawing.Point(3, 105);
            this.currentWaveLabel.Name = "currentWaveLabel";
            this.currentWaveLabel.Size = new System.Drawing.Size(73, 13);
            this.currentWaveLabel.TabIndex = 12;
            this.currentWaveLabel.Text = "Current wave:";
            // 
            // mapLabel
            // 
            this.mapLabel.AutoSize = true;
            this.mapLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.mapLabel.Location = new System.Drawing.Point(3, 86);
            this.mapLabel.Name = "mapLabel";
            this.mapLabel.Size = new System.Drawing.Size(31, 13);
            this.mapLabel.TabIndex = 11;
            this.mapLabel.Text = "Map";
            // 
            // addObjectsLabel
            // 
            this.addObjectsLabel.AutoSize = true;
            this.addObjectsLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.addObjectsLabel.Location = new System.Drawing.Point(6, 0);
            this.addObjectsLabel.Name = "addObjectsLabel";
            this.addObjectsLabel.Size = new System.Drawing.Size(76, 13);
            this.addObjectsLabel.TabIndex = 9;
            this.addObjectsLabel.Text = "Add Objects";
            // 
            // descriptionLabel
            // 
            this.descriptionLabel.AutoSize = true;
            this.descriptionLabel.Location = new System.Drawing.Point(3, 216);
            this.descriptionLabel.Name = "descriptionLabel";
            this.descriptionLabel.Size = new System.Drawing.Size(33, 13);
            this.descriptionLabel.TabIndex = 8;
            this.descriptionLabel.Text = "None";
            // 
            // selectedLabel
            // 
            this.selectedLabel.AutoSize = true;
            this.selectedLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.selectedLabel.Location = new System.Drawing.Point(3, 197);
            this.selectedLabel.Name = "selectedLabel";
            this.selectedLabel.Size = new System.Drawing.Size(57, 13);
            this.selectedLabel.TabIndex = 7;
            this.selectedLabel.Text = "Selected";
            // 
            // addShipButton
            // 
            this.addShipButton.Location = new System.Drawing.Point(6, 47);
            this.addShipButton.Name = "addShipButton";
            this.addShipButton.Size = new System.Drawing.Size(148, 25);
            this.addShipButton.TabIndex = 1;
            this.addShipButton.Text = "Add Ship";
            this.addShipButton.UseVisualStyleBackColor = true;
            this.addShipButton.Click += new System.EventHandler(this.button1_Click);
            // 
            // addPlanetButton
            // 
            this.addPlanetButton.Location = new System.Drawing.Point(6, 16);
            this.addPlanetButton.Name = "addPlanetButton";
            this.addPlanetButton.Size = new System.Drawing.Size(148, 25);
            this.addPlanetButton.TabIndex = 0;
            this.addPlanetButton.Text = "Add Planet";
            this.addPlanetButton.UseVisualStyleBackColor = true;
            this.addPlanetButton.Click += new System.EventHandler(this.PrintTextBoxText_Click);
            // 
            // shipPanel
            // 
            this.shipPanel.Controls.Add(this.shipPilot);
            this.shipPanel.Controls.Add(this.shipPilotLabel);
            this.shipPanel.Controls.Add(this.shipTypeLabel);
            this.shipPanel.Controls.Add(this.shipType);
            this.shipPanel.Controls.Add(this.shipDeleteButton);
            this.shipPanel.Controls.Add(this.shipWaveLabel);
            this.shipPanel.Controls.Add(this.shipWave);
            this.shipPanel.Controls.Add(this.shipPositionLabel);
            this.shipPanel.Controls.Add(this.shipPosX);
            this.shipPanel.Controls.Add(this.shipPosY);
            this.shipPanel.Controls.Add(this.shipPosZ);
            this.shipPanel.Location = new System.Drawing.Point(0, 232);
            this.shipPanel.Name = "shipPanel";
            this.shipPanel.Size = new System.Drawing.Size(157, 248);
            this.shipPanel.TabIndex = 10;
            // 
            // shipPilot
            // 
            this.shipPilot.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.shipPilot.FormattingEnabled = true;
            this.shipPilot.Items.AddRange(new object[] {
            "Standard",
            "Kamikaze",
            "Coward"});
            this.shipPilot.Location = new System.Drawing.Point(6, 138);
            this.shipPilot.Name = "shipPilot";
            this.shipPilot.Size = new System.Drawing.Size(121, 21);
            this.shipPilot.TabIndex = 15;
            this.shipPilot.SelectedIndexChanged += new System.EventHandler(this.shipPilot_SelectedIndexChanged);
            // 
            // shipPilotLabel
            // 
            this.shipPilotLabel.AutoSize = true;
            this.shipPilotLabel.Location = new System.Drawing.Point(6, 122);
            this.shipPilotLabel.Name = "shipPilotLabel";
            this.shipPilotLabel.Size = new System.Drawing.Size(49, 13);
            this.shipPilotLabel.TabIndex = 14;
            this.shipPilotLabel.Text = "Pilot (AI):";
            // 
            // shipTypeLabel
            // 
            this.shipTypeLabel.AutoSize = true;
            this.shipTypeLabel.Location = new System.Drawing.Point(6, 80);
            this.shipTypeLabel.Name = "shipTypeLabel";
            this.shipTypeLabel.Size = new System.Drawing.Size(54, 13);
            this.shipTypeLabel.TabIndex = 13;
            this.shipTypeLabel.Text = "Ship type:";
            // 
            // shipType
            // 
            this.shipType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.shipType.FormattingEnabled = true;
            this.shipType.Items.AddRange(new object[] {
            "Phantom",
            "Arrowhead",
            "Speedster",
            "Hellreaver"});
            this.shipType.Location = new System.Drawing.Point(6, 96);
            this.shipType.Name = "shipType";
            this.shipType.Size = new System.Drawing.Size(121, 21);
            this.shipType.TabIndex = 12;
            this.shipType.SelectedIndexChanged += new System.EventHandler(this.shipType_SelectedIndexChanged);
            // 
            // shipDeleteButton
            // 
            this.shipDeleteButton.Location = new System.Drawing.Point(6, 180);
            this.shipDeleteButton.Name = "shipDeleteButton";
            this.shipDeleteButton.Size = new System.Drawing.Size(75, 23);
            this.shipDeleteButton.TabIndex = 11;
            this.shipDeleteButton.Text = "Remove";
            this.shipDeleteButton.UseVisualStyleBackColor = true;
            this.shipDeleteButton.Click += new System.EventHandler(this.deleteButton_Click);
            // 
            // shipWaveLabel
            // 
            this.shipWaveLabel.AutoSize = true;
            this.shipWaveLabel.Location = new System.Drawing.Point(6, 54);
            this.shipWaveLabel.Name = "shipWaveLabel";
            this.shipWaveLabel.Size = new System.Drawing.Size(39, 13);
            this.shipWaveLabel.TabIndex = 10;
            this.shipWaveLabel.Text = "Wave:";
            // 
            // shipWave
            // 
            this.shipWave.Location = new System.Drawing.Point(45, 52);
            this.shipWave.Name = "shipWave";
            this.shipWave.Size = new System.Drawing.Size(51, 20);
            this.shipWave.TabIndex = 9;
            this.shipWave.ValueChanged += new System.EventHandler(this.numericUpDown1_ValueChanged);
            // 
            // shipPositionLabel
            // 
            this.shipPositionLabel.AutoSize = true;
            this.shipPositionLabel.Location = new System.Drawing.Point(3, 10);
            this.shipPositionLabel.Name = "shipPositionLabel";
            this.shipPositionLabel.Size = new System.Drawing.Size(47, 13);
            this.shipPositionLabel.TabIndex = 4;
            this.shipPositionLabel.Text = "Position:";
            // 
            // shipPosX
            // 
            this.shipPosX.Location = new System.Drawing.Point(9, 26);
            this.shipPosX.Name = "shipPosX";
            this.shipPosX.Size = new System.Drawing.Size(40, 20);
            this.shipPosX.TabIndex = 8;
            this.shipPosX.TextChanged += new System.EventHandler(this.positionChangedX);
            // 
            // shipPosY
            // 
            this.shipPosY.Location = new System.Drawing.Point(56, 26);
            this.shipPosY.Name = "shipPosY";
            this.shipPosY.Size = new System.Drawing.Size(40, 20);
            this.shipPosY.TabIndex = 8;
            this.shipPosY.TextChanged += new System.EventHandler(this.positionChangedY);
            // 
            // shipPosZ
            // 
            this.shipPosZ.Location = new System.Drawing.Point(101, 26);
            this.shipPosZ.Name = "shipPosZ";
            this.shipPosZ.Size = new System.Drawing.Size(40, 20);
            this.shipPosZ.TabIndex = 8;
            this.shipPosZ.TextChanged += new System.EventHandler(this.positionChangedZ);
            // 
            // planetPanel
            // 
            this.planetPanel.Controls.Add(this.planetScaleLabel);
            this.planetPanel.Controls.Add(this.planetScale);
            this.planetPanel.Controls.Add(this.planetDeleteButton);
            this.planetPanel.Controls.Add(this.planetPosZ);
            this.planetPanel.Controls.Add(this.planetPosY);
            this.planetPanel.Controls.Add(this.planetPosX);
            this.planetPanel.Controls.Add(this.planetPositionLabel);
            this.planetPanel.Controls.Add(this.planetSolid);
            this.planetPanel.Controls.Add(this.planetTextureLabel);
            this.planetPanel.Controls.Add(this.planetTexture);
            this.planetPanel.Location = new System.Drawing.Point(0, 232);
            this.planetPanel.Name = "planetPanel";
            this.planetPanel.Size = new System.Drawing.Size(157, 179);
            this.planetPanel.TabIndex = 10;
            // 
            // planetScaleLabel
            // 
            this.planetScaleLabel.AutoSize = true;
            this.planetScaleLabel.Location = new System.Drawing.Point(6, 97);
            this.planetScaleLabel.Name = "planetScaleLabel";
            this.planetScaleLabel.Size = new System.Drawing.Size(37, 13);
            this.planetScaleLabel.TabIndex = 13;
            this.planetScaleLabel.Text = "Scale:";
            // 
            // planetScale
            // 
            this.planetScale.Location = new System.Drawing.Point(49, 94);
            this.planetScale.Name = "planetScale";
            this.planetScale.Size = new System.Drawing.Size(46, 20);
            this.planetScale.TabIndex = 12;
            this.planetScale.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            // 
            // planetDeleteButton
            // 
            this.planetDeleteButton.Location = new System.Drawing.Point(3, 143);
            this.planetDeleteButton.Name = "planetDeleteButton";
            this.planetDeleteButton.Size = new System.Drawing.Size(75, 23);
            this.planetDeleteButton.TabIndex = 11;
            this.planetDeleteButton.Text = "Remove";
            this.planetDeleteButton.UseVisualStyleBackColor = true;
            this.planetDeleteButton.Click += new System.EventHandler(this.deleteButton_Click);
            // 
            // planetPosZ
            // 
            this.planetPosZ.Location = new System.Drawing.Point(101, 26);
            this.planetPosZ.Name = "planetPosZ";
            this.planetPosZ.Size = new System.Drawing.Size(40, 20);
            this.planetPosZ.TabIndex = 10;
            this.planetPosZ.TextChanged += new System.EventHandler(this.positionChangedZ);
            // 
            // planetPosY
            // 
            this.planetPosY.Location = new System.Drawing.Point(55, 26);
            this.planetPosY.Name = "planetPosY";
            this.planetPosY.Size = new System.Drawing.Size(40, 20);
            this.planetPosY.TabIndex = 9;
            this.planetPosY.TextChanged += new System.EventHandler(this.positionChangedY);
            // 
            // planetPosX
            // 
            this.planetPosX.Location = new System.Drawing.Point(9, 26);
            this.planetPosX.Name = "planetPosX";
            this.planetPosX.Size = new System.Drawing.Size(40, 20);
            this.planetPosX.TabIndex = 8;
            this.planetPosX.TextChanged += new System.EventHandler(this.positionChangedX);
            // 
            // planetPositionLabel
            // 
            this.planetPositionLabel.AutoSize = true;
            this.planetPositionLabel.Location = new System.Drawing.Point(3, 10);
            this.planetPositionLabel.Name = "planetPositionLabel";
            this.planetPositionLabel.Size = new System.Drawing.Size(47, 13);
            this.planetPositionLabel.TabIndex = 4;
            this.planetPositionLabel.Text = "Position:";
            // 
            // planetSolid
            // 
            this.planetSolid.AutoSize = true;
            this.planetSolid.Location = new System.Drawing.Point(6, 120);
            this.planetSolid.Name = "planetSolid";
            this.planetSolid.Size = new System.Drawing.Size(113, 17);
            this.planetSolid.TabIndex = 3;
            this.planetSolid.Text = "Solid (not scenery)";
            this.planetSolid.UseVisualStyleBackColor = true;
            this.planetSolid.CheckedChanged += new System.EventHandler(this.checkBox1_CheckedChanged);
            // 
            // planetTextureLabel
            // 
            this.planetTextureLabel.AutoSize = true;
            this.planetTextureLabel.Location = new System.Drawing.Point(3, 51);
            this.planetTextureLabel.Name = "planetTextureLabel";
            this.planetTextureLabel.Size = new System.Drawing.Size(46, 13);
            this.planetTextureLabel.TabIndex = 1;
            this.planetTextureLabel.Text = "Texture:";
            // 
            // planetTexture
            // 
            this.planetTexture.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.planetTexture.FormattingEnabled = true;
            this.planetTexture.Items.AddRange(new object[] {
            "Ice",
            "Purple",
            "Pollution",
            "Earth"});
            this.planetTexture.Location = new System.Drawing.Point(6, 67);
            this.planetTexture.Name = "planetTexture";
            this.planetTexture.Size = new System.Drawing.Size(142, 21);
            this.planetTexture.TabIndex = 0;
            this.planetTexture.SelectedIndexChanged += new System.EventHandler(this.comboBox1_SelectedIndexChanged);
            // 
            // RenderBox
            // 
            this.RenderBox.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.RenderBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.RenderBox.Location = new System.Drawing.Point(0, 24);
            this.RenderBox.Name = "RenderBox";
            this.RenderBox.Size = new System.Drawing.Size(1747, 1018);
            this.RenderBox.TabIndex = 3;
            // 
            // statusStrip
            // 
            this.statusStrip.Location = new System.Drawing.Point(0, 1020);
            this.statusStrip.Name = "statusStrip";
            this.statusStrip.Size = new System.Drawing.Size(1747, 22);
            this.statusStrip.TabIndex = 4;
            this.statusStrip.Text = "statusStrip1";
            // 
            // form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1904, 1042);
            this.Controls.Add(this.statusStrip);
            this.Controls.Add(this.RenderBox);
            this.Controls.Add(this.sidePanel);
            this.Controls.Add(this.menuStrip);
            this.MainMenuStrip = this.menuStrip;
            this.MinimumSize = new System.Drawing.Size(500, 290);
            this.Name = "form1";
            this.Text = "Level editor";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.menuStrip.ResumeLayout(false);
            this.menuStrip.PerformLayout();
            this.sidePanel.ResumeLayout(false);
            this.sidePanel.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.currentWaveSelector)).EndInit();
            this.shipPanel.ResumeLayout(false);
            this.shipPanel.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.shipWave)).EndInit();
            this.planetPanel.ResumeLayout(false);
            this.planetPanel.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip;
        private System.Windows.Forms.Panel sidePanel;
        private System.Windows.Forms.Panel RenderBox;
        private System.Windows.Forms.Button addPlanetButton;
        private System.Windows.Forms.StatusStrip statusStrip;
        private System.Windows.Forms.Button addShipButton;
        private System.Windows.Forms.Label descriptionLabel;
        private System.Windows.Forms.Label selectedLabel;
        private System.Windows.Forms.Label addObjectsLabel;
        private System.Windows.Forms.Panel planetPanel;
        private System.Windows.Forms.Label planetTextureLabel;
        private System.Windows.Forms.ComboBox planetTexture;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem newToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator;
        private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveAsToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.CheckBox planetSolid;
        private System.Windows.Forms.MaskedTextBox planetPosZ;
        private System.Windows.Forms.MaskedTextBox planetPosY;
        private System.Windows.Forms.MaskedTextBox planetPosX;
        private System.Windows.Forms.Label planetPositionLabel;
        private System.Windows.Forms.Button planetDeleteButton;
        private System.Windows.Forms.Label planetScaleLabel;
        private System.Windows.Forms.TextBox planetScale;

        private System.Windows.Forms.Panel shipPanel;
        private System.Windows.Forms.Label shipPositionLabel;
        private System.Windows.Forms.TextBox shipPosX;
        private System.Windows.Forms.TextBox shipPosY;
        private System.Windows.Forms.TextBox shipPosZ;
        private System.Windows.Forms.Button shipDeleteButton;
        private System.Windows.Forms.Label shipWaveLabel;
        private System.Windows.Forms.NumericUpDown shipWave;
        private System.Windows.Forms.NumericUpDown currentWaveSelector;
        private System.Windows.Forms.Label currentWaveLabel;
        private System.Windows.Forms.Label mapLabel;
        private System.Windows.Forms.ComboBox shipType;
        private System.Windows.Forms.ComboBox shipPilot;
        private System.Windows.Forms.Label shipPilotLabel;
        private System.Windows.Forms.Label shipTypeLabel;
    }
}

