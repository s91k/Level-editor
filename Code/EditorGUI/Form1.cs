using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Windows.Interop;

namespace Example
{
    public partial class form1 : Form
    {
        enum SelectedType 
        { 
            None = 0, 
            Planet = 1, 
            Ship = 2
        };

        SelectedType m_currentSelected = SelectedType.None;
        CppCLI m_GameEngine = null;
        bool m_APILoaded = false;

        public form1()
        {
            InitializeComponent();

            this.m_GameEngine = new CppCLI();

            this.ResizeEnd += new EventHandler(form1_ResizeEnd);
            this.Resize += new EventHandler(form1_Resize);

            this.m_GameEngine.Init(RenderBox.Handle, RenderBox.Width, RenderBox.Height);
            this.m_APILoaded = true;

            this.KeyPreview = true;
            this.RenderBox.MouseClick += new MouseEventHandler(RenderBox_MouseClick);
            this.KeyDown += new KeyEventHandler(handle_KeyDown);
        }

        public void GameLoop()
        {
            while (this.Created)
            {
                Run();
                Application.DoEvents(); 
            }
        }
        //This is our update/Renderloop
        private void Run()
        {
            if (m_APILoaded)
            {
                //Run the GameEngine for one frame
                m_GameEngine.ProcessFrame();
            }
        }

        void form1_Resize(object sender, EventArgs e)
        {
            //Hantera när maximize knappen trycks
            if (this.WindowState == FormWindowState.Maximized)
            {
                m_GameEngine.OnResize(RenderBox.Width, RenderBox.Height);
            }
            //När man återgår till "normal" state igen så hantera de också
            else if (this.WindowState == FormWindowState.Normal)
            {
                m_GameEngine.OnResize(RenderBox.Width, RenderBox.Height);
            }
        }

        void form1_ResizeEnd(object sender, EventArgs e)
        {
            this.m_GameEngine.OnResize(RenderBox.Width, RenderBox.Height);
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void PrintTextBoxText_Click(object sender, EventArgs e)
        {
            this.m_GameEngine.SpawnPlanet();    
        }

        private void RenderBox_MouseClick(object sender, MouseEventArgs e)
        {
            this.m_GameEngine.HandleMouseClick(e.X, e.Y);
            this.label4.Text = "Type: " + this.m_GameEngine.getSelectedInfo();
            this.RenderBox.Select();

            //Remove the existing panel
            switch (this.m_currentSelected)
            {
                case SelectedType.None:
                    //Nothing to remove
                    break;
                case SelectedType.Planet:
                    this.panel1.Controls.Remove(this.planetPanel);
                    break;
                case SelectedType.Ship:
                    this.panel1.Controls.Remove(this.shipPanel);
                    break;
            }

            this.m_currentSelected = (SelectedType)this.m_GameEngine.getSelectedType();

            //Add the new panel
            switch (this.m_currentSelected)
            {
                case SelectedType.Planet:
                    this.panel1.Controls.Add(this.planetPanel);

                    this.planetTexture.SelectedIndex = this.m_GameEngine.getSelectedTexture();
                    this.planetPosX.Text = this.m_GameEngine.getSelectedPosX().ToString();
                    this.planetPosY.Text = this.m_GameEngine.getSelectedPosY().ToString();
                    this.planetPosZ.Text = this.m_GameEngine.getSelectedPosZ().ToString();
                    this.planetScale.Text = this.m_GameEngine.getSelectedScale().ToString();
                    this.planetSolid.Checked = this.m_GameEngine.getSelectedSolid();

                    break;

                case SelectedType.Ship:
                    this.panel1.Controls.Add(this.shipPanel);

                    this.shipPosX.Text = this.m_GameEngine.getSelectedPosX().ToString();
                    this.shipPosY.Text = this.m_GameEngine.getSelectedPosY().ToString();
                    this.shipPosZ.Text = this.m_GameEngine.getSelectedPosZ().ToString();
                    this.shipWave.Value = this.m_GameEngine.getWave();
                    this.shipType.SelectedIndex = this.m_GameEngine.getSelectedShipType();
                    this.shipPilot.SelectedIndex = this.m_GameEngine.getSelectedPilot();

                    break;

                case SelectedType.None:

                    break;
            }
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void label5_Click(object sender, EventArgs e)
        {

        }

        private void label6_Click(object sender, EventArgs e)
        {

        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.m_GameEngine.exportLevel("testLevel.txt");
            MessageBox.Show("Exporterat");
        }

        private void saveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();

            saveFileDialog.CheckPathExists = true;
            saveFileDialog.DefaultExt = "txt";
            saveFileDialog.Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
            saveFileDialog.FilterIndex = 2;
            saveFileDialog.ShowDialog();

            if(saveFileDialog.FileName != "")
            {
                this.m_GameEngine.exportLevel(saveFileDialog.FileName);
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.m_GameEngine.SpawnEnemy();
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            this.m_GameEngine.SetSelectedTexture(planetTexture.SelectedIndex);
        }

        private void deleteButton_Click(object sender, EventArgs e)
        {
            if (this.m_GameEngine.getSelectedType() != 0)
            {
                this.m_GameEngine.removeSelected();
            }

            SelectedType tmp = (SelectedType)this.m_GameEngine.getSelectedType();

            if (tmp == SelectedType.None)
            {
                //Remove the existing panel
                switch (this.m_currentSelected)
                {
                    case SelectedType.None:
                        //Nothing to remove
                        break;
                    case SelectedType.Planet:
                        this.panel1.Controls.Remove(this.planetPanel);
                        break;
                    case SelectedType.Ship:
                        this.panel1.Controls.Remove(this.shipPanel);
                        break;
                }

                this.m_currentSelected = tmp;
                this.label4.Text = "Type: " + this.m_GameEngine.getSelectedInfo();
            }
        }

        private void positionChangedX(object send, EventArgs e)
        {
            try
            {
                float x = 0.0f;

                switch (this.m_currentSelected)
                {
                    case SelectedType.Planet:
                        x = float.Parse(this.planetPosX.Text);
                        break;

                    case SelectedType.Ship:
                        x = float.Parse(this.shipPosX.Text);
                        break;
                }

                this.m_GameEngine.setSelectedPosX(x);
            }
            catch (System.FormatException formatException)
            {
                //MessageBox.Show(formatException.ToString());
            }
        }

        private void positionChangedY(object send, EventArgs e)
        {
            try
            {
                float y = 0.0f;

                switch (this.m_currentSelected)
                {
                    case SelectedType.Planet:
                        y = float.Parse(this.planetPosY.Text);
                        break;

                    case SelectedType.Ship:
                        y = float.Parse(this.shipPosY.Text);
                        break;
                }

                this.m_GameEngine.setSelectedPosY(y);
            }
            catch (System.FormatException formatException)
            {
                //MessageBox.Show(formatException.ToString());
            }
        }

        private void positionChangedZ(object send, EventArgs e)
        {
            try
            {
                float z = 0.0f;

                switch (this.m_currentSelected)
                {
                    case SelectedType.Planet:
                        z = float.Parse(this.planetPosZ.Text);
                        break;

                    case SelectedType.Ship:
                        z = float.Parse(this.shipPosZ.Text);
                        break;
                }

                this.m_GameEngine.setSelectedPosZ(z);
            }
            catch (System.FormatException formatException)
            {
                //MessageBox.Show(formatException.ToString());
            }
        }

        private void label1_Click_1(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            try
            {
                float scale = float.Parse(this.planetScale.Text);
                this.m_GameEngine.setSelectedScale(scale);
            }
            catch (System.FormatException formatException)
            {
                //MessageBox.Show(formatException.ToString());
            }
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            this.m_GameEngine.setSelectedSolid(planetSolid.Checked);
        }

        private void numericUpDown1_ValueChanged(object sender, EventArgs e)
        {
            System.Windows.Forms.NumericUpDown senderControl = (System.Windows.Forms.NumericUpDown)sender;

            if (senderControl.Value != this.m_GameEngine.getWave())
            {
                if (sender == numericUpDown1)
                {
                    this.m_GameEngine.setWave((int)numericUpDown1.Value, false);
                }
                else
                {
                    this.m_GameEngine.setWave((int)shipWave.Value, true);
                    this.shipWave.Value = this.m_GameEngine.getWave();
                }

                numericUpDown1.Value = this.m_GameEngine.getWave();
                SelectedType tmp = (SelectedType)this.m_GameEngine.getSelectedType();

                if (tmp == SelectedType.None)
                {
                    //Remove the existing panel
                    switch (this.m_currentSelected)
                    {
                        case SelectedType.None:
                            //Nothing to remove
                            break;
                        case SelectedType.Planet:
                            this.panel1.Controls.Remove(this.planetPanel);
                            break;
                        case SelectedType.Ship:
                            this.panel1.Controls.Remove(this.shipPanel);
                            break;
                    }

                    this.m_currentSelected = tmp;
                    this.label4.Text = "Type: " + this.m_GameEngine.getSelectedInfo();
                }
            }

        }

        private void shipType_SelectedIndexChanged(object sender, EventArgs e)
        {
            this.m_GameEngine.setSelectedShipType(this.shipType.SelectedIndex);
        }

        private void newToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.m_GameEngine.clearLevel();

            //Remove the existing panel
            switch (this.m_currentSelected)
            {
                case SelectedType.None:
                    //Nothing to remove
                    break;
                case SelectedType.Planet:
                    this.panel1.Controls.Remove(this.planetPanel);
                    break;
                case SelectedType.Ship:
                    this.panel1.Controls.Remove(this.shipPanel);
                    break;
            }

            numericUpDown1.Value = this.m_GameEngine.getWave();
            this.label4.Text = "Type: " + this.m_GameEngine.getSelectedInfo();
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();

            openFileDialog.CheckPathExists = true;
            openFileDialog.DefaultExt = "txt";
            openFileDialog.Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
            openFileDialog.FilterIndex = 2;
            openFileDialog.ShowDialog();

            if (openFileDialog.FileName != "")
            {
                this.m_GameEngine.importLevel(openFileDialog.FileName);
            }
        }

        private void shipPilot_SelectedIndexChanged(object sender, EventArgs e)
        {
            this.m_GameEngine.setSelectedPilot(this.shipPilot.SelectedIndex);
        }

        private void handle_KeyDown(object sender, KeyEventArgs e)
        {
            switch (e.KeyCode)
            {
                case Keys.W:    //Up
                    this.m_GameEngine.moveCameraUp();
                    break;

                case Keys.S:    //Down
                    this.m_GameEngine.moveCameraDown();
                    break;

                case Keys.A:    //Left
                    this.m_GameEngine.moveCameraLeft();
                    break;

                case Keys.D:    //Right
                    this.m_GameEngine.moveCameraRight();
                    break;
            }

            e.Handled = true;
        }
    }
}
