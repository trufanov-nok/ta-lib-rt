using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Tests
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
            performTests();
        }

        private void performTests()
        {
            button1.Enabled = false;
            button2.Enabled = false;
            new CoreTests();
            new TimeseriesRequirementTests();
            Log.AppendText("\nTest Completed");
            button1.Enabled = true;
            button2.Enabled = true;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            performTests();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}