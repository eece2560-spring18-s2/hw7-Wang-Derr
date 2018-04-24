#include "member.h"

#include <queue>

#include "database.h"
#include <limits>

namespace algdb {

void Member::DumpConnections() {
  std::cout << "(" << member_id << ")";
  for (auto &m : connecting_members) {
    auto conn = m.second;
    std::cout << "->" << conn.dst->member_id << 
      "(" << conn.group->group_id << ")";
  }
  std::cout << "\n";
}

void Member::PathToMemberBFS(uint64_t dst_member_id) {
  this->color = COLOR_GRAY;
  this->parent = NULL;
  std::queue<Member*> q;
  q.push(this);
  while (!q.empty()) {
    Member *v = q.front();
    q.pop();
    for (auto u : v->connecting_members) {
      auto mc = u.second;
      auto md = mc.dst;
      if (md->member_id == dst_member_id) {
        md->parent = v;
        PrintPath(md);
        return;
      }
      if (md->color == COLOR_WHITE) {
        md->color = COLOR_GRAY;
        md->parent = v;
        q.push(md);
      }
    }
    v->color = COLOR_BLACK;
  }
}

Member *Member::DLS(Member *n, int d, uint64_t dst_member_id) {
  if (d == 0 && n->member_id == dst_member_id) {
    return n;
  }
  if (d > 0) {
    for (auto child : n->connecting_members) {
      auto mc = child.second;
      auto f = DLS(mc.dst, d-1, dst_member_id);
      if (f != NULL) {
        mc.dst->parent = n;
        return f;
      }
    }
  }
  return NULL;
}

void Member::PathToMemberIDDFS(uint64_t dst_member_id) {
  for (int d = 0; d < std::numeric_limits<int>::max(); d++) {
    Member *f = DLS(this, d, dst_member_id);
    if (f != NULL) {
      PrintPath(f);
      return;
    }
  }
}
  
void Member::PrintPath(Member* dst) {
  Member *curr = dst;
  while(curr && curr != this) {
    std::cout << curr->member_name << " <- ";
    curr = curr->parent;
  }
  std::cout << this->member_name << "\n";
}

}
