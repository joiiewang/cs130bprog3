#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void getResult(string s1, string s2, double changed, double skipped, double match){
    //cout << changed << " " << skipped << " " << match << endl;
    int i;
    int j;

    int l1 = s1.size();
    int l2 = s2.size();


    //vector<vector<double> > scoreT(l2+l1+1, vector<double>(l1+l2+1));
    vector<double> v(l2+l1+1, 0);
    vector<vector<double>> scoreT(l2+l1+1, v);

    for(i=0;i<=(l1+l2);i++){
        scoreT[i][0] = (double)i * skipped;
        scoreT[0][i] = (double)i * skipped;
    }


    for(i=1;i<=l1;i++){
        for(j=1;j<=l2;j++){
            if(s1[i-1]==s2[j-1]){
                scoreT[i][j] = scoreT[i-1][j-1]+match;
            }
            else{
                scoreT[i][j] = max({scoreT[i-1][j-1]+changed,
                                    scoreT[i-1][j]+skipped,
                                    scoreT[i][j-1]+skipped});
            }
        }
    }

    int l = l1+l2;

    i=l1;
    j=l2;

    int xp = l;
    int yp = l;

    int xans[l+1];
    int yans[l+1];

    while(!(i==0||j==0)){
        if(s1[i-1]==s2[j-1]){
            xans[xp--] = (int)s1[i - 1];
            yans[yp--] = (int)s2[j - 1];
            i--; 
            j--;
        }
        else if(scoreT[i-1][j-1]+changed == scoreT[i][j]){
            xans[xp--] = (int)s1[i - 1];
            yans[yp--] = (int)s2[j - 1];
            i--; 
            j--;

        }
        else if(scoreT[i-1][j]+skipped == scoreT[i][j]){
            xans[xp--] = (int)s1[i - 1];
            yans[yp--] = (int)'_';
            i--;
        }
        else if(scoreT[i][j-1]+skipped == scoreT[i][j]){
            xans[xp--] = (int)'_';
            yans[yp--] = (int)s2[j - 1];
            j--;
        }
    }

    while(xp>0){
        if(i>0 )xans[xp--] = (int)s1[i--];
        else xans[xp--] = (int)'_';
    }
    while(yp>0){
        if(j>0) yans[yp--] = (int)s2[j--];
        else yans[yp--] = (int)'_';
    }

    int ind = 1;
    for(i=l;i>=1;i--){
        if ((char)yans[i] == '_' && (char)xans[i] == '_'){
            ind = i + 1;
            break;
        }
    }

    cout<<scoreT[l1][l2]<<endl;

    for(i = ind;i<=l;i++){
        cout<<(char)xans[i];
    }
    cout<< "\n";
    for(i = ind;i<=l;i++){
        cout<<(char)yans[i];
    }
    cout<<"\n"; 




}

int main(int argc, char*argv[]){
    int i=0;
    double match = 2.0;
    double changed = -0.5;
    double skipped = -1.0;
    string strand1;
    string strand2;
    while(i < argc){
        string s(argv[i]);
        if(s == "-m"){
            i++;
            string m(argv[i]);
            match = stod(m);

        }
        else if(s == "-c"){
            i++;
            string c(argv[i]);
            changed = stod(c);

        }
        else if(s == "-d"){
            i++;
            string d(argv[i]);
            skipped = stod(d);

        }
        else if(s=="-1"){
            i++;
            ifstream myFile(argv[i]);
            if(!myFile.is_open()) throw runtime_error("could not open file");
            getline(myFile, strand1);
        }
        else if(s=="-2"){
            i++;
            ifstream myFile(argv[i]);
            if(!myFile.is_open()) throw runtime_error("could not open file");
            getline(myFile, strand2);
        }
        i++;

    }
    getResult(strand1, strand2, changed, skipped, match);

    /* ifstream myFile(argv[1]);

    if(!myFile.is_open()) throw runtime_error("could not open file");
    
    string strand1;
    string strand2;
    double match;
    double changed;
    double skipped;

    string line;

    while(getline(myFile,line)){
        match = stod(line.substr(line.find('=')+1,line.find(' ')-line.find('=')-1));
        line = line.substr(line.find(' ')+1);
        changed = stod(line.substr(line.find('=')+1,line.find(' ')-line.find('=')-1));
 
        line = line.substr(line.find(' ')+1);
        skipped = stod(line.substr(line.find('=')+1,line.find(' ')-line.find('=')-1));

        line = line.substr(line.find(' ')+1);
        string file1 = line.substr(line.find('=')+1,line.find(' ')-line.find('=')-1) + ".txt";
        line= line.substr(line.find(' ')+1);
        string file2 = line.substr(line.find('=')+1,line.find(' ')-line.find('=')-1)+ ".txt";

        ifstream input1File(file1);
        ifstream input2File(file2);
        if(!input1File.is_open()) throw runtime_error("could not open file");
        if(!input2File.is_open()) throw runtime_error("could not open file");
        getline(input1File, strand1);
        getline(input2File, strand2);
        //cout << strand1 << " " << strand2 << endl; 
        getResult(strand1, strand2, changed, skipped, match);
        }

 */
    return 0;
}