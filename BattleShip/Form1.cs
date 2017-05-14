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
    public partial class Form1 : Form
    {
        int[,] mas_pl1 = new int[10, 10];
        int[,] mas_pl2 = new int[10, 10];
        public Form2 form;
        // struct Ship
        //{
        //    public int x;       // начальная позиция
        //    public int y;
        //    public int p;       // количество палуб
        //    public bool orient; // ориентация в пространстве (0-вертикальное (false), 1-горизонтальное (true))
        //    public int pp;  // количество подбитых палуб

        //    public Ship (int xx, int yy, int pp, bool orientx, int ppp)
        //    {
        //        x = xx;
        //        y = yy;
        //        p = pp;
        //        orient = orientx;
        //        pp = ppp;
        //    }
        //}
        //Ship[] ship_pl1 = new Ship[10];
        //Ship[] ship_pl2 = new Ship[10];

        //Ship ship_init(Ship* ship_)
        //{
        //    ship_[0] = { 0, 0, 4, 1, 0 };
        //    ship_[1] = ship_[2] = { 0, 0, 3, 1, 0 };
        //    ship_[3] = ship_[4] = ship_[5] = { 0, 0, 2, 1, 0 };
        //    ship_[6] = ship_[7] = ship_[8] = ship_[9] = { 0, 0, 1, 1, 0 };
        //    return *ship_;
        //}
        //Ship ship_pl2[0] = new Ship ( 0, 0, 4, true, 0 );
        //ship_[1] = ship_[2] = { 0, 0, 3, 1, 0 };
        //ship_[3] = ship_[4] = ship_[5] = { 0, 0, 2, 1, 0 };
        //ship_[6] = ship_[7] = ship_[8] = ship_[9] = { 0, 0, 1, 1, 0 };

        public Form1()
        {
            InitializeComponent();
        }

        private void ButtonClick(Button button)
        {
            button.FlatAppearance.MouseOverBackColor = Color.WhiteSmoke;
            if (mas_pl2[0, 0] == 0) // ?
            {
                button.BackgroundImage = Properties.Resources.bloomer;
                toolStripStatusLabel1.Text = "Мимо";
            }
            if (mas_pl2[0, 0] == 1)
            {
                button.BackgroundImage = Properties.Resources.kill;
            }
        }

        private void toolStripMenuItem1_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            ButtonClick(button1);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            ButtonClick(button2);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            ButtonClick(button3);
        }

        private void button4_Click(object sender, EventArgs e)
        {
            ButtonClick(button4);
        }

        private void button17_Click(object sender, EventArgs e)
        {
            button17.BackgroundImage = Properties.Resources.bloomer;
        }

        private void menuStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {

        }

        private void toolStripMenuItem2_Click(object sender, EventArgs e)
        {
            groupBox1.Enabled = true;
            groupBox2.Enabled = true;
            form = new Form2();
            form.Tag = this;
            form.Show();
        }

        private void оToolStripMenuItem_Click(object sender, EventArgs e)
        {
            AboutBox1 AboutBox1 = new AboutBox1(this);
            AboutBox1.Show();
        }

        private void button201_Click(object sender, EventArgs e)
        {
            button201.Visible = false;
            //ship_init(ship_pl2);
        }
    }
}
