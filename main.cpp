#include <iostream>
#include <map>
#include <string>
#include <exception>
#include <limits>


void dataInput(std::map<std::string, int>&);
bool inputArticleControl( const std::string&);
bool inputNumCtrl(const int&);
void baseVisu(std::map<std::string, int>&);

int main() {

    std::map<std::string, int > productBase;
    int count=0;

    while (count<3){
        dataInput(productBase);
        count++;
    }

    baseVisu(productBase);
}


void dataInput(std::map<std::string, int>& base ){

    std::string article;
    int num ;

    do{
        std::cout << "Please enter the "<< base.size()+1<<" article in the base: ";
        std::cin >> article;

    } while (!inputArticleControl(article));

    do {
        std::cout << " Please enter the num of  "<<article<<": ";
        std::cin >> num;
    } while (!inputNumCtrl(num));

    std::pair<std::string, int> actPair =std::make_pair(article,num);
    base.insert(actPair);

}

bool inputArticleControl( const std::string& inputArticle){

    for(int i =0;i< inputArticle.size();i++){
        if (inputArticle[i]<'0'||inputArticle[i]>'z'){
            std::cout << "Incorrect input, repeat!\n";
            return false;
        }
    }
    return true;
}

bool inputNumCtrl(const int& inputNum){

    if (std::cin.good()){
        if (inputNum <=0 || inputNum >100000 ){
            std::cout << "Input num error, repeat\n";
            return false;
        }
        return true;
    }
    else{
        std::cout << "Input num error,repeat \n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    };
}

void baseVisu(std::map<std::string, int>& base){
    for (auto it: base){
        std::cout <<it.first<<" "<<it.second<<"\n";
    }
}