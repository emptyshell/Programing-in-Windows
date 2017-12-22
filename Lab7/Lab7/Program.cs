using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing;
using System.Media;

namespace Lab7
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
        }
    }
}

namespace PW_Labs_Csharp
{
    public partial class Form_lab1 : Form
    {
        public Form_lab1()
        {
            InitializeComponent();
        }

        private void Form_lab1_Load(object sender, EventArgs e)
        {
            SoundPlayer simpleSound = new SoundPlayer(Properties.Resources.musical002);
            simpleSound.Play();
            text_label.Text = "Lucrarea de laborator al studentului Coroletchi Octavian grupa TI-154";
            //text_label.Left = 200;
        }
    }
}

namespace PW_Labs_Csharp
{
    public partial class Form_lab2 : Form
    {
        public Form_lab2()
        {
            InitializeComponent();
            Image image = PW_Labs_Csharp.Properties.Resources.Bmp_file_Icon_256;
            pb1.Image = image;
            pb1.Width = image.Width;
            pb1.Height = image.Height;
            pb1.CreateGraphics();
        }
        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }
        int i = 0;
        bool reverse = false;
        private void draw_panel_Paint(object sender, PaintEventArgs e)
        {
            Pen blueP = new Pen(Color.Blue);
            SolidBrush blueB = new SolidBrush(Color.Blue);
            SolidBrush redB = new SolidBrush(Color.Red);
            SolidBrush crimsonB = new SolidBrush(Color.DarkMagenta);
            Graphics dc = CreateGraphics();
            dc.DrawLine(blueP, new Point(200, 225), new Point(950, 225));
            dc.DrawLine(blueP, new Point(950, 225), new Point(950, 300));
            dc.DrawLine(blueP, new Point(200, 300), new Point(950, 300));
            dc.DrawLine(blueP, new Point(200, 225), new Point(200, 300));
            dc.FillEllipse(blueB, 200, 350, 750, 100);
            dc.FillRectangle(redB, 200, 460, 750, 100);
            dc.DrawRectangle(blueP, 200, 460, 750, 100);
            e.Graphics.FillEllipse(crimsonB, i, 0, 50, 50);
        }





        private void timer1_Tick(object sender, EventArgs e)
        {
            if (reverse == false)
                i += 10;
            else if (reverse == true)
                i -= 10;
            if (i == (970))
                reverse = true;
            else if (i == 0)
                reverse = false;
            Invalidate(true);
        }

    }
}

namespace PW_Labs_Csharp
{
    public partial class Form_lab3 : Form
    {
        public Form_lab3()
        {
            InitializeComponent();
        }
        private void Form_lab3_Load(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {
            Point[] points = new Point[] { new Point { X = 150, Y = 300 }, new Point { X = 250, Y = 0 }, new Point { X = 400, Y = 1300 }, new Point { X = 500, Y = 200 } };
            SolidBrush myBrush = new SolidBrush(Color.MediumAquamarine);
            e.Graphics.DrawBezier(new Pen(Color.Magenta), points[0], points[1], points[2], points[3]);
            //e.Graphics.DrawLine(new Pen(Color.Magenta), new Point(points[0].X + 500, points[0].Y), new Point(points[0].X + 500, points[0].Y));
            for (double t = 0; t < 1; t = t + 0.0001)
            {
                int x = Convert.ToInt32(Math.Pow((1 - t), 3) * points[0].X + 3 * t * Math.Pow((1 - t), 2) * points[1].X + 3 * t * t * (1 - t) * points[2].X + t * t * t * points[3].X);
                int y = Convert.ToInt32(Math.Pow((1 - t), 3) * points[0].Y + 3 * t * Math.Pow((1 - t), 2) * points[1].Y + 3 * t * t * (1 - t) * points[2].Y + t * t * t * points[3].Y);
                e.Graphics.FillRectangle(myBrush, x + 500, y, 1, 1);
            }
        }
    }
}

namespace PW_Labs_Csharp
{
    public partial class Form_lab4 : Form
    {
        public Form_lab4()
        {
            InitializeComponent();
        }
        int i = 0;
        int x = 0;
        int y = 0;
        int angle = 0;
        bool reverse = false;
        float scale_x = 1;



        private void draw_panel_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.FillEllipse(new SolidBrush(Color.Red), 0 + i, 0, 50, 50);

        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (reverse == false)
                i += 10;
            else if (reverse == true)
                i -= 10;
            if (i > (this.Width - 150))
                reverse = true;
            else if (i == 0)
                reverse = false;
            Invalidate(true);
        }

        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Right)
                x += 15;
            if (e.KeyCode == Keys.Left)
                x -= 15;
            if (e.KeyCode == Keys.Up)
                y -= 15;
            if (e.KeyCode == Keys.Down)
                y += 15;
            if (e.KeyCode == Keys.CapsLock)
                angle += 10;
            if (e.KeyCode == Keys.ShiftKey)
                angle -= 10;
        }

        private void Form_lab4_Load(object sender, EventArgs e)
        {
            panel1.BackColor = Color.FromArgb(0, 0, 0, 0);

        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {
            Image image = PW_Labs_Csharp.Properties.Resources.Bmp_file_Icon_256;
            Graphics dc = CreateGraphics();
            RectangleF rect = new RectangleF(25 + x, 25 + y, this.Width, this.Height);
            Rectangle srect = new Rectangle(0, 0, 1200, 800);
            dc.TranslateTransform((float)(x + image.Width / 2), (float)(y + image.Height / 2));
            dc.RotateTransform(angle);
            dc.TranslateTransform(-(float)(x + image.Width / 2), -(float)(y + image.Height / 2));
            dc.DrawImage(image, rect, srect, GraphicsUnit.Pixel);
            Pen blueP = new Pen(Color.Blue);
            SolidBrush blueB = new SolidBrush(Color.Blue);
            SolidBrush redB = new SolidBrush(Color.Red);
            SolidBrush crimsonB = new SolidBrush(Color.DarkMagenta);
        }

    }
}

namespace PW_Labs_Csharp
{
    public partial class Form_lab5 : Form
    {
        public Form_lab5()
        {
            InitializeComponent();
        }
        private void Form_lab5_Load(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private Point[] points = new Point[] { new Point { X = 150, Y = 600 }, new Point { X = 450, Y = 0 }, new Point { X = 600, Y = 1000 }, new Point { X = 1000, Y = 200 } };
        int x = 0, y = 0;
        private void panel1_Paint(object sender, PaintEventArgs e)
        {

            SolidBrush myBrush = new SolidBrush(Color.MediumAquamarine);
            e.Graphics.DrawBezier(new Pen(Color.Magenta, 3), points[0], points[1], points[2], points[3]);
            Image image = PW_Labs_Csharp.Properties.Resources.Bmp_file_Icon_256;
            e.Graphics.DrawImage(image, x, y);
        }

        private void panel1_MouseDown(object sender, MouseEventArgs e)
        {

        }

        private void panel1_MouseClick(object sender, MouseEventArgs e)
        {


        }

        private void panel1_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                points[1].X = Cursor.Position.X;
                points[1].Y = Cursor.Position.Y;
                Refresh();
            }
            if (e.Button == MouseButtons.Right)
            {
                x = Cursor.Position.X - 250;
                y = Cursor.Position.Y - 250;
                Refresh();
            }
        }
    }
}


namespace PW_Labs_Csharp
{
    public partial class Form_lab6 : Form
    {
        public Form_lab6()
        {
            InitializeComponent();
        }
        private void Form_lab6_Load(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        double x = 0, y = 0;
        double startX = 570, startY = 441;
        //Seconds
        double sec_endX = 570, sec_endY = 180;
        double const_sec_endX = 570, const_sec_endY = 180;
        //Minutes
        double min_endX = 570, min_endY = 195;
        double const_min_endX = 570, const_min_endY = 195;
        //Hours
        double h_endX = 570, h_endY = 270;
        double const_h_endX = 570, const_h_endY = 270;
        double deg90InRad = 3.14159265358979324 / 30;
        void Rotate_Sec(double deg90InRad)
        {
            x = sec_endX;
            y = sec_endY;
            x -= startX;
            y -= startY;
            sec_endX = (x * Math.Cos(deg90InRad)) - (y * Math.Sin(deg90InRad));
            sec_endY = (x * Math.Sin(deg90InRad)) + (y * Math.Cos(deg90InRad));
            sec_endX += startX;
            sec_endY += startY;
        }

        void Rotate_Min(double deg90InRad)
        {
            x = min_endX;
            y = min_endY;
            x -= startX;
            y -= startY;
            min_endX = (x * Math.Cos(deg90InRad)) - (y * Math.Sin(deg90InRad));
            min_endY = (x * Math.Sin(deg90InRad)) + (y * Math.Cos(deg90InRad));
            min_endX += startX;
            min_endY += startY;
        }
        void Rotate_Hour(double deg90InRad)
        {
            x = h_endX;
            y = h_endY;
            x -= startX;
            y -= startY;
            h_endX = (x * Math.Cos(deg90InRad)) - (y * Math.Sin(deg90InRad));
            h_endY = (x * Math.Sin(deg90InRad)) + (y * Math.Cos(deg90InRad));
            h_endX += startX;
            h_endY += startY;
        }
        private void panel1_Paint(object sender, PaintEventArgs e)
        {

            SolidBrush myBrush = new SolidBrush(Color.MediumAquamarine);
            Image image = PW_Labs_Csharp.Properties.Resources.clock;
            RectangleF rect = new RectangleF(271, 140, 596, 600);
            e.Graphics.DrawImage(image, rect);
            //Seconds Line--------------------------------------
            float temp;
            temp = DateTime.Now.Second;
            while (temp > 0)
            {
                Rotate_Sec(deg90InRad);
                temp--;
            }
            e.Graphics.DrawLine(new Pen(Color.Blue, 1), (float)startX, (float)startY, (float)sec_endX, (float)sec_endY);
            sec_endX = const_sec_endX;
            sec_endY = const_sec_endY;

            //Minute Line---------------------------------------------
            temp = DateTime.Now.Minute;
            while (temp > 0)
            {
                Rotate_Min(deg90InRad);
                temp--;
            }
            temp = DateTime.Now.Second;
            Rotate_Min(deg90InRad * ((temp * 100 / 60) / 100));
            e.Graphics.DrawLine(new Pen(Color.Black, 3), (float)startX, (float)startY, (float)min_endX, (float)min_endY);
            min_endX = const_min_endX;
            min_endY = const_min_endY;

            //Hour Line----------------------------------------
            temp = DateTime.Now.Hour;
            if (temp > 12) temp = temp - 12;
            while (temp > 0)
            {
                Rotate_Hour(deg90InRad * 5);
                temp--;
            }
            temp = DateTime.Now.Minute;
            Rotate_Hour(deg90InRad * 5 * ((temp * 100 / 60) / 100));
            e.Graphics.DrawLine(new Pen(Color.Black, 6), (float)startX, (float)startY, (float)h_endX, (float)h_endY);
            h_endX = const_h_endX;
            h_endY = const_h_endY;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {

            label1.Text = DateTime.Now.ToString("HH:mm:ss");

            panel1.Refresh();


        }
    }
}


