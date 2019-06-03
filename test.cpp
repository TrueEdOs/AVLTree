#include <bits/stdc++.h>
#include "avl_tree.h"
using namespace std;

int main()
{
    int mode;
    cout << "1 TIME TEST.\n2 MANUAL TEST\n CHOOSE\n";
    cin >> mode;
    if(mode > 2 || mode < 1)
        return 0;
    if(mode == 2)
    {
        AVLTree<int> tree;
        while(true)
        {
            int q, x;
            bool the_end = false;
            cout <<"\n\n1 ADD\n2 REMOVE\n3 SHOW\n4 EXIT\n";
            cin >> q;
            switch(q)
            {
            case 1:
                cin >> x;
                tree.insert(x);
                break;
            case 2:
                cin >> x;
                tree.remove(x);
                break;
            case 3:
                tree.print();
                break;
            default:
                the_end = true;
            }

            if(the_end)
                break;
        }
        return 0
    }

    mt19937 rnd(666);
    int n = 1000000;
    vector<int> selection;
    for(int i = 0; i < n; i++)
        selection.push_back(rnd() % 1000000000);

    AVLTree<int> tree;
    multiset<int> q;
    {
        chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
        for(auto & x : selection)
            tree.insert(x);
        for(int i = 0; i < n; i += 2)
            tree.remove(selection[i]);
        chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
        chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
        cout << "It took me " << time_span.count() << " seconds.";
    }
    cout << endl;
    {
        chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
        for(auto & x : selection)
            q.insert(x);
        for(int i = 0; i < n; i += 2)
            q.erase(selection[i]);
        chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
        chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
        cout << "It took me " << time_span.count() << " seconds.";
    }

    return 0;
}
