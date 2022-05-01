#include <iostream>

#define NEG_INF 0
#define POS_INF UINT32_MAX
#define pt std::pair<uint32_t, uint32_t>
#define log2(n) (31 - __builtin_clz(n) + (__builtin_popcount(n)!=1))
#define pow2(n) (1u<<(log2(n)+1u))

pt **alloc(uint32_t height, uint32_t width) {
    pt **matrix = new pt *[height];
    for (uint32_t i = 0; i < height; ++i) {
        matrix[i] = new pt[width];
        for (uint32_t j = 0; j < width; ++j) {
            matrix[i][j] = pt(NEG_INF, POS_INF);
        }
    }
    return matrix;
}

template<typename T>
void dealloc(T **matrix, uint32_t height) {
    for (uint32_t i = 0; i < height; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

class seg_tree_2d {
private:
    uint32_t height, width;
    uint32_t **matrix;
    pt **seg_tree_y_axis;
    pt **seg_tree;

    void segment_horizontally(uint32_t low, uint32_t high, uint32_t pos,
                              uint32_t y) {
        if (high == low) {
            seg_tree_y_axis[y][pos] = pt(matrix[y][low], matrix[y][low]);
        } else {
            uint32_t mid = (low + high) / 2;
            segment_horizontally(low, mid, 2 * pos, y);
            segment_horizontally(mid + 1, high, 2 * pos + 1, y);
            seg_tree_y_axis[y][pos] = pt(
                    std::max(seg_tree_y_axis[y][2 * pos].first, seg_tree_y_axis[y][2 * pos + 1].first),
                    std::min(seg_tree_y_axis[y][2 * pos].second, seg_tree_y_axis[y][2 * pos + 1].second));
        }
    }

    void segment_vertically(uint32_t low, uint32_t high, uint32_t pos) {
        if (high == low) {
            for (uint32_t i = 1; i < pow2(width); i++) {
                seg_tree[pos][i] = seg_tree_y_axis[low][i];
            }
        } else {
            uint32_t mid = (low + high) / 2;
            segment_vertically(low, mid, 2 * pos);
            segment_vertically(mid + 1, high, 2 * pos + 1);
            for (uint32_t i = 1; i < pow2(width); i++) {
                seg_tree[pos][i] = pt(std::max(seg_tree[2 * pos][i].first, seg_tree[2 * pos + 1][i].first),
                                      std::min(seg_tree[2 * pos][i].second, seg_tree[2 * pos + 1][i].second));
            }
        }
    }

    pt horizontal_query(uint32_t pos, uint32_t start, uint32_t end, uint32_t x1,
                        uint32_t x2, uint32_t node) {
        if (x2 < start || end < x1) {
            return pt(NEG_INF, POS_INF);
        }

        if (x1 <= start && end <= x2) {
            return seg_tree[node][pos];
        }

        uint32_t mid = (start + end) / 2;
        pt p1 = horizontal_query(2 * pos, start, mid,
                                 x1, x2, node);

        pt p2 = horizontal_query(2 * pos + 1, mid + 1, end, x1, x2, node);

        return pt(std::max(p1.first, p2.first), std::min(p1.second, p2.second));
    }

    pt vertical_query(uint32_t pos, uint32_t start, uint32_t end, uint32_t y1,
                      uint32_t y2, uint32_t x1, uint32_t x2) {
        if (y2 < start || end < y1) {
            return pt(NEG_INF, POS_INF);
        }

        if (y1 <= start && end <= y2) {
            return (horizontal_query(1, 1, width, x1, x2, pos));
        }

        uint32_t mid = (start + end) / 2;
        pt p1 = vertical_query(2 * pos, start, mid, y1, y2, x1, x2);
        pt p2 = vertical_query(2 * pos + 1, mid + 1, end, y1, y2, x1, x2);

        return pt(std::max(p1.first, p2.first), std::min(p1.second, p2.second));
    }

public:
    seg_tree_2d(uint32_t height, uint32_t width, uint32_t **matrix) {
        this->height = height;
        this->width = width;
        this->matrix = matrix;
        seg_tree_y_axis = alloc(height, pow2(width));
        seg_tree = alloc(pow2(height), pow2(width));
        for (uint32_t y = 0; y < height; ++y) {
            segment_horizontally(0, width - 1, 1, y);
        }
        segment_vertically(0, height - 1, 1);
    }

    ~seg_tree_2d() {
        dealloc<pt >(seg_tree_y_axis, height);
        dealloc<pt >(seg_tree, pow2(height));
    }

    pt query(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2) {
        return vertical_query(1, 1, height, x1 + 1, x2 + 1, y1 + 1, y2 + 1);
    }
};


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    uint32_t n, m, k;
    std::cin >> n >> m >> k;
    auto **fertility = new uint32_t *[n];
    for (uint32_t i = 0; i < n; i++) {
        fertility[i] = new uint32_t[m];
        for (uint32_t j = 0; j < m; j++) {
            std::cin >> fertility[i][j];
        }
    }
    seg_tree_2d tree(n, m, fertility);
    for (uint32_t i = 0; i < k; ++i) {
        uint32_t x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        pt result = tree.query(x1, y1, x2, y2);
        std::cout << result.first - result.second << "\n";
    }
    dealloc<uint32_t>(fertility, n);
    return 0;
}
