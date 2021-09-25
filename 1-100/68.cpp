#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>


int main()
{
        std::string lv_sMax;
        std::vector<unsigned int> lv_Possibilities;
        for (unsigned int lv_uI = 1; lv_uI < 11; ++lv_uI)
                lv_Possibilities.push_back(lv_uI);

        while (std::next_permutation(lv_Possibilities.begin(), lv_Possibilities.end()))
        {

          const unsigned int lc_uSum = lv_Possibilities[0] + lv_Possibilities[1] + lv_Possibilities[lv_Possibilities.size()-1];
          bool lv_bFulfills = true;
          const unsigned int lc_uFirstValue = lv_Possibilities[0];
          for (unsigned int lv_uI = 1; lv_uI < 9; lv_uI+=2)
          {
                if (lv_Possibilities[lv_uI + 1 ] < lc_uFirstValue || lc_uSum != (lv_Possibilities[lv_uI] + lv_Possibilities[lv_uI + 1 ] + lv_Possibilities[lv_uI + 2]))
                {
                    lv_bFulfills = false;
                    break;
                }
          }

          if (lv_bFulfills)
          {
                std::stringstream SS;
                SS << lv_Possibilities[0] << lv_Possibilities[9] << lv_Possibilities[1] << lv_Possibilities[2] << lv_Possibilities[1] << lv_Possibilities[3] << lv_Possibilities[4] << lv_Possibilities[3] << lv_Possibilities[5] << lv_Possibilities[6] << lv_Possibilities[5] << lv_Possibilities[7] << lv_Possibilities[8] << lv_Possibilities[7] << lv_Possibilities[9]; 
                const std::string lc_sValue = SS.str();
                if (lc_sValue.size() == 16 && lc_sValue>lv_sMax)
                {
                        lv_sMax = lc_sValue;
                }
          } 
        }
        std::cout << lv_sMax << std::endl;
       
        return 0;
}  
