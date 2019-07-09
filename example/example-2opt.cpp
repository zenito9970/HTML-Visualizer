#include "../html_visualizer.hpp"
#include <iostream>
#include <random>
#include <algorithm>
#include <utility>
using namespace std;
using namespace HtmlVisualizer;

using P = pair<int, int>;

vector<P> gen_random_nodes(int num_nodes) {
    vector<P> res;
    mt19937 mt(random_device{}());
    uniform_int_distribution<> rng(0, 80);
    for(int i = 0; i < num_nodes; ++i) {
        res.push_back(make_pair(rng(mt), rng(mt)));
    }
    return res;
}

template <class Func>
double two_opt(vector<int>& indexes, const Func& cost) {
    const int n = indexes.size() - 1;
    double best_improve = 0;
    int best_l = 0;
    int best_r = 0;
    for(int l = 0; l < n; ++l) {
        const int from1 = indexes[l];
        const int to1 = indexes[l+1];
        for(int r = l + 1; r < n; ++r) {
            const int from2 = indexes[r];
            const int to2 = indexes[r+1];
            const double prev_cost = cost(from1, to1) + cost(from2, to2);
            const double new_cost = cost(from1, from2) + cost(to1, to2);
            const double improve = prev_cost - new_cost;
            if(best_improve < improve) {
                best_improve = improve;
                best_l = l;
                best_r = r;
            }
        }
    }
    if(best_l != best_r) {
        reverse(indexes.begin() + best_l + 1, indexes.begin() + best_r + 1);
        return best_improve;
    } else {
        return 0;
    }
}

void draw_sequence(Vis& vis, const vector<P>& nodes, const vector<int>& indexes) {
    for(int i = 0; i < indexes.size() - 1; ++i) {
        int x1 = nodes[indexes[i]].first * 10;
        int y1 = nodes[indexes[i]].second * 10;
        int x2 = nodes[indexes[i+1]].first * 10;
        int y2 = nodes[indexes[i+1]].second * 10;
        vis.line(x1, y1, x2, y2);
    }
    for(P pos: nodes) {
        int x = pos.first * 10;
        int y = pos.second * 10;
        vis.circle(x, y, 5);
    }
}

int main() {
    Vis vis("example-2opt.html");
    const int num_nodes = 20;
    vector<P> nodes = gen_random_nodes(num_nodes);
    auto cost = [&](int from, int to) {
        return sqrt(pow(nodes[from].first - nodes[to].first, 2) + pow(nodes[from].second - nodes[to].second, 2));
    };
    vector<int> indexes(num_nodes + 1);
    iota(indexes.begin(), indexes.end(), 0);
    indexes[num_nodes] = 0;

    draw_sequence(vis, nodes, indexes);
    while(1e-8 < two_opt(indexes, cost)) {
        vis.new_page();
        draw_sequence(vis, nodes, indexes);
    }

    return 0;
}
