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
using BinarySearchTreeCLI;
using System.Text.RegularExpressions;

namespace BinarySearchTreeWPF
{
    public partial class MainWindow : Window
    {
        private TreeWrapper wrapper;
        const int MAX = 20000010;
        const int ADD = 10000000;
        List<int> notAdded = new List<int>();
        Point[] points = new Point[MAX];
        bool[] used = new bool[MAX];
        Dictionary<Point, int> row = new Dictionary<Point, int>();
        public MainWindow()
        {
            InitializeComponent();
            myGrid.Background = Brushes.Pink;
            TextBox1.Focus();
            wrapper = new TreeWrapper();
        }
        private void RemoveTreeContents()
        {
            for (int i = 0; i < MAX; i++)
                used[i] = false;
            for (int i = myGrid.Children.Count - 1; i >= 0; i--)
            {
                UIElement el;
                if ((el = myGrid.Children[i]) is Label)
                    myGrid.Children.Remove(el);
                else
                if ((el = myGrid.Children[i]) is Line)
                    myGrid.Children.Remove(el);
            }
        }
        private void AddTreeContents()
        {
            for (int i = 0; i < wrapper.InOrderW().Length; i++)
            {
                int cur = wrapper.InOrderW()[i];
                cur += ADD;
                if (used[cur]) continue;
                used[cur] = true;
                Label lbl = new Label();
                lbl.FontSize = 20;
                lbl.Width = 90;
                lbl.Height = 35;
                lbl.Background = Brushes.MediumVioletRed;
                lbl.VerticalAlignment = VerticalAlignment.Top;
                lbl.HorizontalAlignment = HorizontalAlignment.Left;
                lbl.HorizontalContentAlignment = HorizontalAlignment.Center;
                Grid.SetColumn(lbl, 1);
                lbl.Content = (cur - ADD).ToString();
                int prev;
                if (i == 0)
                {
                    points[cur].X = myGrid.ColumnDefinitions[1].ActualWidth/2;
                    points[cur].Y = 0;
                    lbl.Margin = new Thickness(points[cur].X, points[i].Y, 0, 0);
                    row[points[cur]] = 1;
                    myGrid.Children.Add(lbl);
                }
                else
                {
                    prev = wrapper.InOrderW()[i - 1];
                    prev += ADD;
                    points[cur].Y = points[prev].Y + 110;
                    if (prev < cur)
                    {
                        points[cur].X = points[prev].X + (50 - (row[points[prev]] * 5)) * 10;
                    }
                    else
                    {
                        points[cur].X = points[prev].X - (50 - (row[points[prev]] * 5)) * 10;
                    }
  
                    if (points[cur].X + lbl.Width >= myGrid.ColumnDefinitions[1].ActualWidth || points[cur].Y + lbl.Height >= myGrid.Height || 50 - (row[points[prev]] * 5) <= 0 || points[cur].X < 0)
                    {
                        points[cur] = points[prev];
                        notAdded.Add(cur);
                        continue;
                    }
                    lbl.Margin = new Thickness(points[cur].X, points[cur].Y, 0, 0);
                    row[new Point(points[cur].X, points[cur].Y)] = row[points[prev]] + 1;
                    myGrid.Children.Add(lbl);
                    Line l = new Line();
                    l.X1 = points[prev].X + lbl.Width / 2;
                    l.X2 = points[cur].X + lbl.Width / 2;
                    l.Y1 = points[prev].Y + lbl.Height;
                    l.Y2 = points[cur].Y;
                    Grid.SetColumn(l, 1);
                    l.StrokeThickness = 3;
                    l.Stroke = Brushes.Black;
                    myGrid.Children.Add(l);
                }
            }
            if (notAdded.Count != 0)
            {
                string message = "";
                for (int j = 0; j < notAdded.Count() - 1; j++)
                {
                    int i = notAdded[j];
                    if (j < notAdded.Count() - 2) message = message + (i - ADD).ToString() + ", ";
                    else message = message + (i - ADD).ToString();
                    wrapper.RemoveW(i - ADD);
                }
                if (notAdded.Count > 1) MessageBox.Show($"Числата {message} и {notAdded[notAdded.Count - 1] - ADD} не бяха добавени поради ограниченията.");
                else MessageBox.Show($"Числото {notAdded[notAdded.Count - 1] - ADD} не беше добавено поради ограниченията.");
                wrapper.RemoveW(notAdded[notAdded.Count - 1] - ADD);
                notAdded.Clear();
            }
        }
        private void Button1_Click(object sender, RoutedEventArgs e)
        {
            {
                RemoveTreeContents();
                string text = TextBox1.Text;
                int number = 0;
                bool usable = true, toAdd = false, flag=false;
                foreach (char c in text)
                {
                    if (string.IsNullOrWhiteSpace(c.ToString()))
                    {
                        if (toAdd && usable)
                        {
                            if (flag) number = -number;
                            wrapper.AddW(number);
                        }
                        flag = false;
                        usable = true;
                        toAdd = false;
                        number = 0;
                        continue;
                    }
                    if (c == '-') flag = true;
                    if (usable && c >= '0' && c <= '9') { number = number * 10 + c - '0'; toAdd = true; }
                    if (number >= 10000000)
                    {
                        usable = false;
                    }
                }
                if (flag) number = -number;
                if (toAdd && usable) wrapper.AddW(number);
                AddTreeContents();
                TextBox1.Clear();
                TextBox1.Focus();
            }
        }
        private void Clear_Button_Click(object sender, RoutedEventArgs e)
        {
            RemoveTreeContents();
            wrapper.DeleteW();
            TextBox1.Focus();
        }
        private void About_Click(object sender, RoutedEventArgs e)
        {
            About abt = new About();
            abt.Show();
        }
        private void TextBox1_PreviewExecuted(object sender, ExecutedRoutedEventArgs e)
        {
            if (e.Command == ApplicationCommands.Paste)
            {
                e.Handled = true;
            }
        }
        private void TextBox1_PreviewTextInput(object sender, TextCompositionEventArgs e)
        {
            string s = e.Text;
            foreach(char c in s)
            {
                if ((c >= '0' && c <= '9') || c=='-')
                {
                    continue;
                }
                else e.Handled = true;             
            }
        }      
    }
}
