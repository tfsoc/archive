using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace sudoku0._2
{
    class Highscore : IComparable<Highscore>
    {
        public string name{get;private set;}
        public int time { get; private set; }
        public int level { get; private set; }
        
        /// <summary>
        /// Creates an instance of highscore record
        /// </summary>
        /// <param name="line">string in format "%level% %userName% %time%"</param>
        public Highscore(string line)
        {
            string[] tokens = line.Split(' ');
            name = tokens[1];
            try
            {
                time = int.Parse(tokens[2]);
            }
            catch
            {
                time = -1;
            }
            try
            {
                level = int.Parse(tokens[0]);
            }
            catch
            {
                level = -1;
            }
        }
        public override string ToString()
        {
            return Convert.ToString(name + " \t" + time);
        }

        public int CompareTo(Highscore other)
        {
            if (other == null) return 1;
            return time.CompareTo(other.time);
        }

        /// <summary>
        /// Define the is greater than operator.
        /// </summary>
        /// <param name="operand1"></param>
        /// <param name="operand2"></param>
        /// <returns></returns>
        public static bool operator >(Highscore operand1, Highscore operand2)
        {
            return operand1.CompareTo(operand2) == 1;
        }

        /// <summary>
        ///  Define the is less than operator.
        /// </summary>
        /// <param name="operand1"></param>
        /// <param name="operand2"></param>
        /// <returns></returns>
        public static bool operator <(Highscore operand1, Highscore operand2)
        {
            return operand1.CompareTo(operand2) == -1;
        }

        /// <summary>
        ///  Define the is greater than or equal to operator.
        /// </summary>
        /// <param name="operand1"></param>
        /// <param name="operand2"></param>
        /// <returns></returns>
        public static bool operator >=(Highscore operand1, Highscore operand2)
        {
            return operand1.CompareTo(operand2) >= 0;
        }

        /// <summary>
        /// Define the is less than or equal to operator.
        /// </summary>
        /// <param name="operand1"></param>
        /// <param name="operand2"></param>
        /// <returns></returns>
        public static bool operator <=(Highscore operand1, Highscore operand2)
        {
            return operand1.CompareTo(operand2) <= 0;
        }
    }
}
