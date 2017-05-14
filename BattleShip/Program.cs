using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BattleShip
{
    static class Data
    {
        public static string name1 { get; set; }
        public static string name2 { get; set; }
        public static int set_ship { get; set; }
        public static int mode_play { get; set; }
        public static string ipadress { get; set; }
        public static string port { get; set; }
    }

    static class Program
    {
        /// <summary>
        /// Главная точка входа для приложения.
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
