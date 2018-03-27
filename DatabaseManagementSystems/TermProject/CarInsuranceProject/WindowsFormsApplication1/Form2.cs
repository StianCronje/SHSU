using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Form3 nw1 = new Form3();
            nw1.Show();
            this.Hide();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            Form1 nw = new Form1();
            nw.Show();
            this.Hide();

        }

        private void button5_Click_1(object sender, EventArgs e)
        {
            DialogResult dialog = MessageBox.Show("Are you sure you want to logout ?", "Log Out", MessageBoxButtons.YesNo);
            if (dialog == DialogResult.Yes)
            {
                Form1 nw = new Form1();
                nw.Show();
                this.Hide();
            }
            else if (dialog == DialogResult.No)
            {
              
            }
           
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Form4 nw = new Form4();
            nw.Show();
            this.Hide();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            Form5 nw = new Form5();
            nw.Show();
            this.Hide();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            Form6 nw = new Form6();
            nw.Show();
            this.Hide();
        }
    }
}
