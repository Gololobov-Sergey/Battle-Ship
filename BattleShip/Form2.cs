using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BattleShip
{
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Data.name1 = textBox1.Text;
            ((Form1)this.Tag).groupBox1.Text = Data.name1;
            if (radioButton1.Checked)
                Data.set_ship = 1;
            else
                Data.set_ship = 2;
            if (radioButton3.Checked)
                Data.mode_play = 1;
            else
            {
                Data.mode_play = 2;
                Data.ipadress = textBox3.Text;
                Data.port = textBox2.Text;
            }
            ((Form1)this.Tag).button201.Visible = true;
            Close();
        }

        private void radioButton4_CheckedChanged(object sender, EventArgs e)
        {
            groupBox4.Enabled = true;
        }

        private void radioButton3_CheckedChanged(object sender, EventArgs e)
        {
            groupBox4.Enabled = false;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            button2.Text = "Ok";
        }
    }
}
