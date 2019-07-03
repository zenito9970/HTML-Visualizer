#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include "../html_visualizer.hpp"
using namespace std;
using namespace HtmlVisualizer;

const vector<string> grid = {
    "##########",
    "#.#......#",
    "#.#...##.#",
    "#...#.##.#",
    "#.#.#....#",
    "#.#...##.#",
    "##########"
};

const int N = max(grid.size(), grid[0].size());
const int S = 800 / N;
using P = pair<int, int>;

void draw_grid(Vis &vis) {
    for(int y = 0; y < grid.size(); ++y) {
        for(int x = 0; x < grid[y].size(); ++x) {
            if(grid[y][x] == '#') {
                vis.rect(S * x, S * y, S, S);
            }
        }
    }
}

void draw_visit(Vis &vis, const vector<vector<int>> &dist) {
    for(int y = 0; y < dist.size(); ++y) {
        for(int x = 0; x < dist[y].size(); ++x) {
            if(dist[y][x] < (1<<29)) {
                vis.rect(S * x, S * y, S, S, Color {100, 100, 100});
            }
        }
    }
}

void draw_route(Vis &vis, const vector<P> &route) {
    for(P p: route) {
        vis.circle(S * (p.first + 0.5), S * (p.second + 0.5), S / 2, Color {255, 0, 0});
    }
}

vector<P> bfs(Vis &vis, P start, P goal) {
    const int dx[4] = {-1, 0, 1, 0};
    const int dy[4] = {0, -1, 0, 1};
    vector<vector<int>> dist(N, vector<int>(N, 1<<29));
    vector<vector<int>> prev(N, vector<int>(N, -1));
    queue<P> q; // (x, y)
    dist[start.second][start.first] = 0;
    q.push(start);
    while(!q.empty()) {
        vis.new_page();
        draw_grid(vis);
        draw_visit(vis, dist);
        P p = q.front();
        q.pop();
        if(p == goal) {
            break;
        }
        for(int i = 0; i < 4; ++i) {
            int nx = p.first + dx[i];
            int ny = p.second + dy[i];
            if(grid[ny][nx] != '#' && dist[p.second][p.first] + 1 < dist[ny][nx]) {
                dist[ny][nx] = dist[p.second][p.first] + 1;
                prev[ny][nx] = i;
                q.push(make_pair(nx, ny));
            }
        }
    }
    P now = goal;
    vector<P> route;
    while(now != start) {
        route.push_back(now);
        vis.new_page();
        draw_grid(vis);
        draw_route(vis, route);
        const int x = now.first;
        const int y = now.second;
        now.first -= dx[prev[y][x]];
        now.second -= dy[prev[y][x]];
    }
    route.push_back(now);
    vis.new_page();
    draw_grid(vis);
    draw_route(vis, route);

    reverse(route.begin(), route.end());
    return route;
}

int main() {
    auto vis = Vis("example.html");
    draw_grid(vis);
    auto route = bfs(vis, make_pair(1, 1), make_pair(8, 5));
    for(P p: route) {
        cout << "(" << p.first << ", " << p.second << "), ";
    }
    cout << endl;
    return 0;
}


