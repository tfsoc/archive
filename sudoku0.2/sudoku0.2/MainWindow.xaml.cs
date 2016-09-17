using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.ComponentModel;
using System.Windows.Threading;
using System.Threading;
using System.Diagnostics;
using System.IO;

namespace sudoku0._2
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private Sudoku _sudoku;
        private TextBox[] mybox= new TextBox[81];
        private StackPanel[] panel = new StackPanel[9];
        private int timerSec;
        private DispatcherTimer dispatcherTimer;
        private bool recordScore;
        private string path = "highscore.txt";
        private List<Highscore> records;
        private int currentLvl;
        private Thread watek;
        private bool _shouldCount;
        public MainWindow()
        {     
            InitializeComponent();
            timerSec = 0;
            //refreshes timer every second
            dispatcherTimer = new System.Windows.Threading.DispatcherTimer(new TimeSpan(0, 0, 0, 1), DispatcherPriority.Normal, delegate
            {
                //timerSec++;
                lblSeconds.Content = "Time: "+timerSec.ToString();
            }, this.Dispatcher);
            dispatcherTimer.Stop();

            watek = new Thread(() => { while (_shouldCount) { Thread.Sleep(1000); timerSec++; } });
            watek.IsBackground = true;
            _shouldCount = false;
            //watek = new Thread(() => { while (_shouldCount) { Thread.Sleep(1000); timerSec++; } });
            //watek.IsBackground = true;
            
            if (!File.Exists(path))
            {
                // Create a file to write to
                using (StreamWriter sw = File.CreateText(path))
                {
                    sw.WriteLine("1 Tom 100");
                    sw.WriteLine("2 Tom 110");
                    sw.WriteLine("3 Tom 120");
                    sw.WriteLine("1 Tom 130");
                    sw.WriteLine("2 Tom 140");
                }
            }

            records = new List<Highscore>();

            string s1 = "";
            s1 += "\n\n";
            _sudoku = new Sudoku();

            textBox1.Text = "HELLO";
            textBox1.TextAlignment = System.Windows.TextAlignment.Center;

            for (int i = 0; i < 9;i++ )
            {
                panel[i] = new StackPanel();
                panel[i].Orientation = System.Windows.Controls.Orientation.Horizontal;
                panel[i].Height = 50;
                panel[i].Width = 450;
                pole.Children.Add(panel[i]);
            }
            for(int i=0;i<81;i++)
            {
                mybox[i] = new TextBox();
                mybox[i].Width = 50;
                mybox[i].TextAlignment = TextAlignment.Center;
                mybox[i].FontSize = 24;
                mybox[i].IsHitTestVisible = false;
                int tmp = _sudoku.game_tab_copy[i];
                mybox[i].Text = "";

                mybox[i].Tag = i;
                mybox[i].TextChanged += new TextChangedEventHandler((sender, e) =>
                {
                    TextBox textBox = (TextBox)sender;
                    int j = int.Parse(textBox.Tag.ToString());
                    if(!textBox.Text.Equals("")){
                        try
                        {
                            int val = int.Parse(textBox.Text);
                            if (textBox.Text.Length != 1) throw new Exception();
                            _sudoku.game_tab_copy[j] = val;
                            if (_sudoku.endGame() == true)
                            {
                                textBox1.Text = "Congrats, You have won!";
                                dispatcherTimer.Stop();
                                _shouldCount = false;
                                //watek.Abort();
                                recordWin();
                            }
                        }
                        catch
                        {
                            textBox1.Text = "You can only use 1-9 numbers";
                            textBox.Text = "0";
                            _sudoku.game_tab_copy[j] = 0;
                        }
                        if (textBox.Text.Equals("0"))
                        {
                            textBox.Text = "";
                        }
                    }

                });
               
                panel[i / 9].Children.Add(mybox[i]);
            }
            for (int i = 0; i < 81; i++)
            {
                int x = i%9;
                int y = i/9;
                if ((x >= 3 && x <= 5 && !(y >= 3 && y <= 5)) || (y >= 3 && y <= 5 && !(x >= 3 && x <= 5)))
                {
                    mybox[i].Background = Brushes.Pink;
                }
                else
                {
                    mybox[i].Background = Brushes.LightBlue;
                }
            }
        }
        /// <summary>
        /// Block input boxes and add highscore record if recordScore value is true
        /// </summary>
        private void recordWin()
        {
            for (int i = 0; i < 81; i++)
            {
                mybox[i].IsReadOnly = true;
                mybox[i].IsTabStop = false;
                mybox[i].IsHitTestVisible = false;
            }
            if (recordScore == true)
            {
                string temp = Microsoft.VisualBasic.Interaction.InputBox("Enter Your name:", "Record Your Highscore", "user");
                temp = temp.Replace(" ", String.Empty);
                using (StreamWriter sw = File.AppendText(path))
                {
                    sw.WriteLine(currentLvl + " " + temp + " " + timerSec.ToString());
                }
                showLeaders();
            }
        }
        /// <summary>
        /// Show top 5 leaders in comboBox selected difficulty level
        /// </summary>
        private void showLeaders()
        {
            using (StreamReader sr = File.OpenText(path))
            {
                string line = "";
                string disp = "";
                string[] dif = { "easy", "normal", "hard" };
                while ((line = sr.ReadLine()) != null)
                {
                    if (line.Length >= 2)
                        records.Add(new Highscore(line));
                }

                records.Sort();
                int top = 0;
                int len = records.Count();
                for (int i = 0; i < len; i++)
                {
                    if (records[i].level == currentLvl)
                    {
                        disp += records[i].ToString() + "\n";
                        top++;
                    }
                    if (top == 5)
                        break;
                }
                MessageBox.Show(disp, "Leaders in "+dif[currentLvl-1]+":");
                records.Clear();
            }
        }
        /// <summary>
        /// Generate new game problem set in selected difficulty level
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void nowaGra_Click(object sender, RoutedEventArgs e)
        {
            _shouldCount = false;
            while(watek.IsAlive)Thread.Sleep(10);
            textBox1.Text = "Good luck";
            showans.IsEnabled = true;
            recordScore = true;
            int lvl = combo1.SelectedIndex+1;
            currentLvl = lvl;
            for (int i = 0; i < 81; i++)
            {
                //mybox[i].Text = "0";
                //_sudoku.game_tab_copy[i] = 0;
                mybox[i].FontWeight = System.Windows.FontWeights.Normal;
                mybox[i].IsReadOnly = false;
                mybox[i].IsTabStop = true;
                mybox[i].IsHitTestVisible = true;
            }
            _sudoku.mix(20);
            _sudoku.newGame(lvl);
            for (int i = 0; i < 81; i++)
            {
                mybox[i].Text = Convert.ToString(_sudoku.game_tab_copy[i]);
                
                if (_sudoku.game_tab_copy[i] != 0)
                {
                    mybox[i].FontWeight = System.Windows.FontWeights.Bold;
                    mybox[i].IsReadOnly = true;
                    mybox[i].IsTabStop = false;
                    mybox[i].IsHitTestVisible = false;
                }
                //textBox1.Text += Convert.ToString(_sudoku.game_tab_copy[i] +" ");
                //if (_sudoku.game_tab_copy[i] == 0) mybox[i].Text = "0";
            }
            timerSec = 0;
            dispatcherTimer.Start();

            watek = new Thread(() =>
            {

                while (_shouldCount)
                {
                    Thread.Sleep(1000); 
                    timerSec++;
                }
            });
            watek.IsBackground = true;
            _shouldCount = true;
            watek.Start();
        }

        /// <summary>
        /// Show answers and do not record the highscore
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Button_Click(object sender, RoutedEventArgs e)
        {
            Button btn = sender as Button;
            btn.IsEnabled = false;
            recordScore = false;
            for (int i = 0; i < 81; i++)
            {
                mybox[i].IsReadOnly = true;
                mybox[i].IsTabStop = false;
                mybox[i].IsHitTestVisible = false;
                mybox[i].Text = _sudoku.tab[i % 9, i / 9].ToString();
            }
            textBox1.Text = "Press new game to continue...";
        }
        /// <summary>
        /// Invoke Show Leaders
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            int tmp = currentLvl;
            currentLvl = combo1.SelectedIndex + 1;
            showLeaders();
            currentLvl = tmp;
        }
    }
}
