#include <algorithm>
#include <vector>
#include <iomanip>
#include <iostream>
#include <mutex>


std::string s = "GATCGAGACAGCATCAGCATCATCATGATAGATAGCACGACAGCTACATCGAATCATGACTACA";

int main()
{
    std::string value = "CAT";
    std::mutex m;
    std::vector < char > vector;
    for (int i = 0; i < s.size(); ++i) {
        vector.push_back(s[i]);
    }
    std::lock_guard < std::mutex > lock(m);
    std::vector<char>::iterator it;
    it = std::find(vector.begin(), vector.end(), value);
    if (it != vector.end()) {
        std::cout << it - vector.begin() + 1;
    }
    else  std::cout << -1;

    return 0;
}
