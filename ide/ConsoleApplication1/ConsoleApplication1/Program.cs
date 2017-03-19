using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApplication1
{
    class Program
    {
        static void Main(string[] args)
        {
            for (uint a = 0; a < 16; a++)
            {
                for (uint m = 0; m < 16; m++)
                {
                    for (uint c = 0; c < 2; c++)
                    {
                        var r = a + m + c;
                        if (((a ^ m ^ r) & 0x10) == 0x10)
                        {
                            if (r <= 9)
                            {
                                Console.WriteLine("FAIL");
                            }
                        }
                        else
                        {
                            if (r > 9)
                            {
                                Console.WriteLine("FAIL for {0} + {1} + {2} = {3}", Convert.ToString(a, 2), Convert.ToString(m, 2), c, Convert.ToString(r, 2));
                            }
                        }
                    }
                }
            }
        }
    }
}
