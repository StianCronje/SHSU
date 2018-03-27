using System;
using System.Windows.Forms;
using System.Data.SQLite;


namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        const string dbLocation = @"data source=C:\Users\Stian\Dropbox\SHSU\DatabaseManagement\Project\ProjectDatabase.db";
        public Form1()
        {
            InitializeComponent();
        }
        public void clean()
        {
            textBox1.Clear();
            textBox2.Clear();

        }

        private void button1_Click(object sender, EventArgs e)
        {
            SQLiteConnection connection;
            var connectionString = (dbLocation + ";Version=3;");
            connection = new SQLiteConnection(connectionString);
            connection.Open();
            SQLiteCommand comm = new SQLiteCommand("select *from User where uID='" + textBox1.Text + "' and pw= '" + textBox2.Text + "'", connection);
            SQLiteDataReader dr = comm.ExecuteReader();
            if (dr.Read())
            {

                Form2 frm = new Form2();
                frm.Show();
                this.Hide();

            }
            else
            {
                MessageBox.Show("Username or Password is incorrect");
                clean();

            }
            connection.Close();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            this.MaximizeBox = false;

        }


    }
}
