using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace sudoku0._2
{
    class Sudoku
    {
        /// <summary>
        /// answer list
        /// </summary>
        public int[,] tab { get; private set; }
        /// <summary>
        /// answer list with blanks for user to fill
        /// </summary>
        public int[,] game_tab { get; private set; }
        Random random = new Random();
        /// <summary>
        /// problem set plus users' answer
        /// </summary>
        public int[] game_tab_copy { get; set; }
        /// <summary>
        /// Creates new instance of sudoku with a sample matrix seed
        /// </summary>
        public Sudoku()
        {
            tab = new int[9, 9];
            game_tab = new int[9, 9];
            game_tab_copy = new int[81];
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    tab[i, j] = (i * 3 + i / 3 + j) % (3 * 3) + 1;
                    game_tab[i, j] = 0;
                    game_tab_copy[i + j * 9] = game_tab[i, j];
                }
            }

        }
        /// <summary>
        /// Counts empty cells
        /// </summary>
        /// <returns>how many cells are left to be filled</returns>
        public int countLeft()
        {
            int left_to_fill = 81;
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    if (game_tab_copy[i + j * 9] != 0) left_to_fill--;
                }
            }
            return left_to_fill;
        }
        /// <summary>
        /// Checks if all cells are filled and filled correctly
        /// </summary>
        /// <returns>true if game solved correctly, false if there was an error</returns>
        public bool endGame()
        {
            if (this.countLeft() != 0)
                return false;

            //if our problemset has a unique solution - only check with answer array
            
            //for (int i = 0; i < 9; i++)
            //{
            //    for (int j = 0; j < 9; j++)
            //    {
            //        if (game_tab_copy[i * 9 + j] != tab[i, j])
            //            return false;
            //    }
            //}

            SudokuSolver.tab = new int[9, 9];
            
            //else we check for 'duplicate'
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    SudokuSolver.tab[i, j] = game_tab_copy[i + j * 9];
                }
            }

            int tmp;
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    tmp = game_tab_copy[i + j * 9];
                    game_tab_copy[i + j * 9] = 0;
                    if (SudokuSolver.check(game_tab_copy[i + j * 9], i, j) == false)
                        return false;
                    game_tab_copy[i + j * 9] = tmp;
                }
            }
            return true;
        }
        
        /// <summary>
        /// amount of givens ranges in each difficulty level : (1)32-48, (2)28-35, (3)24-30
        /// </summary>
        /// <param name="difficulty">1 = easy, 2 = normal and 3 = hard</param>
        public void newGame(int difficulty)
        {
            //this.mix(20);
            int lower_bound, upper_bound, revealed_blocks;
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    game_tab[i, j] = 0;
                }
            }
            switch (difficulty)
            {
                case 1:
                    lower_bound = 4;
                    upper_bound = 6;
                    revealed_blocks = 8;
                    break;
                case 2:
                    lower_bound = 4;
                    upper_bound = 5;
                    revealed_blocks = 7;
                    break;
                case 3:
                    lower_bound = 4;
                    upper_bound = 5;
                    revealed_blocks = 6;
                    break;
                default:
                    lower_bound = 4;
                    upper_bound = 5;
                    revealed_blocks = 7;
                    break;
            }
            //if block (1-9) was already looked through
            bool[] looked = new bool[9];
            for (int i = 0; i < 9; i++)
            {
                looked[i] = false;
            }
            while (revealed_blocks != 0)
            {
                int area = random.Next(9);
                if (looked[area] == false)
                {
                    looked[area] = true;

                    int count = random.Next(lower_bound, upper_bound + 1);
                    while (count != 0)
                    {
                        int x = (area % 3) * 3 + random.Next(3);
                        int y = (area / 3) * 3 + random.Next(3);
                        if (game_tab[x, y] == 0)
                        {
                            count--;
                            game_tab[x, y] = tab[x, y];
                        }
                    }

                    revealed_blocks--;
                }

            }
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    game_tab_copy[i + j * 9] = game_tab[i, j];
                }
            }
        }
        /// <summary>
        /// Transposing sudoku answer matrix
        /// </summary>
        public void transposing()
        {
            for (int i = 0; i < 9; i++)
            {
                for (int j = i; j < 9; j++)
                {
                    Swap<int>(ref tab[i, j], ref tab[j, i]);
                }
            }
        }
        /// <summary>
        /// Swaps two random rows in a block
        /// </summary>
        public void swap_rows_small()
        {
            int line1, line2, area, n1, n2;
            line1 = random.Next(3);
            line2 = random.Next(3);
            area = random.Next(3);
            if (line1 == line2) line2 = (line2 + 1) % 3;
            n1 = area * 3 + line1;
            n2 = area * 3 + line2;
            for (int j = 0; j < 9; j++)
            {
                Swap<int>(ref tab[n1, j], ref tab[n2, j]);
            }

        }
        /// <summary>
        /// Swaps two random columns within a block
        /// </summary>
        public void swap_columns_small()
        {
            this.transposing();
            this.swap_rows_small();
            this.transposing();
        }
        /// <summary>
        /// Swaps two random rows of blocks
        /// </summary>
        public void swap_rows_area()
        {
            int area1, area2, n1, n2;
            area1 = random.Next(3);
            area2 = random.Next(3);
            if (area1 == area2) area2 = (area2 + 1) % 3;

            //a more 'natural' randomization
            //area2 = (area1 + random.Next(1, 3)) % 3;

            for (int i = 0; i < 3; i++)
            {
                n1 = area1 * 3 + i;
                n2 = area2 * 3 + i;
                for (int j = 0; j < 9; j++)
                {
                    Swap<int>(ref tab[n1, j], ref tab[n2, j]);
                }
            }
        }
        /// <summary>
        /// Swaps two random columns of blocks
        /// </summary>
        public void swap_columns_area()
        {
            this.transposing();
            this.swap_rows_area();
            this.transposing();
        }
        /// <summary>
        /// Generates new tab by permutations that dont change the correctness of sudoku matrix
        /// </summary>
        /// <param name="times">determines how many times to permute the matrix</param>
        public void mix(int times = 10)
        {
            Action chosen = () => { };
            Action[] actions = new Action[] { swap_rows_small, swap_rows_area, swap_columns_small, swap_columns_area };
            for (int i = 0; i < times; i++)
            {
                chosen = actions[random.Next(4)];
                chosen();
            }

            //different approach
            //for(int i=0; i < times;  i++)
            //{
            //    int x = random.Next(4);
            //    switch (x)
            //    {
            //        case 0:
            //            this.swap_rows_small();
            //            break;
            //        case 1:
            //            this.swap_rows_area();
            //            break;
            //        case 2:
            //            this.swap_columns_small();
            //            break;
            //        case 3:
            //            this.swap_columns_area();
            //            break;
            //        default:
            //            break;
            //    }
            //}
        }
        /// <summary>
        /// Swaps two variables' values
        /// </summary>
        /// <typeparam name="T">type of variable</typeparam>
        /// <param name="lhs">variable1</param>
        /// <param name="rhs">variable2</param>
        static void Swap<T>(ref T lhs, ref T rhs)
        {
            T temp;
            temp = lhs;
            lhs = rhs;
            rhs = temp;
        }
        /// <summary>
        /// Answer matrix values from left to right, top to buttom forming a answer string
        /// </summary>
        /// <returns>answer string</returns>
        public override string ToString()
        {
            string s = "";
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    s += Convert.ToString(tab[i, j]);
                }
            }
            return s;
        }
    }
}
