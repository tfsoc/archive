using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace sudoku0._2
{
    class SudokuSolver
    {
        static public int[,] tab { get; set; }

        /// <summary>
        /// DFS algorithm based solution existence test
        /// </summary>
        /// <param name="s">matrix of problem in forms of string with values from left to right, top to buttom</param>
        /// <returns>true if solution exists and false otherwise</returns>
        static public bool solution(String s)
        {
            if (s.Length != 81)
            {
                throw new Exception("Podana nieprawidlowa tablica do solucji");
            }
            tab = new int[9, 9];
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    tab[i, j] = int.Parse(s[i * 9 + j].ToString());
                }
            }

            bool ans;
            try
            {
                place(0);
                ans = false;
            }
            catch (Exception e)
            {
                ans = true;
            }
            return ans;
        }
        /// <summary>
        /// search for first good value in position pos
        /// </summary>
        /// <param name="pos">position of current cell</param>
        static public void place(int pos)
        {
            int x, y;
            if (pos == 81)
            {
                throw new Exception();
            }

            x = pos % 9;
            y = pos / 9;

            if (tab[x, y] > 0)
            {
                place(pos + 1);
                return;
            }
            for (int val = 1; val <= 9; val++)
            {
                if (check(val, x, y))
                {
                    tab[x, y] = val;
                    place(pos + 1);
                    tab[x, y] = 0;
                }
            }

        }
        /// <summary>
        /// Check if value val can be placed in cell with indexes X,Y
        /// </summary>
        /// <param name="val">testing value from 0-9</param>
        /// <param name="x">left to right position from 0-9</param>
        /// <param name="y">top to buttom position from 0-9</param>
        /// <returns>true if this value can be places there</returns>
        static public bool check(int val, int x, int y)
        {
            //check horizontal and vertical values
            for (int i = 0; i < 9; i++)
            {
                if (tab[x, i] == val || tab[i, y] == val)
                {
                    return false;
                }
            }
            //check area
            int x1 = (x / 3) * 3; //same as x-(x%3)
            int y1 = (y / 3) * 3;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (tab[x1 + i, y1 + j] == val)
                    {
                        return false;
                    }
                }
            }
            return true;
        }
    }
}
