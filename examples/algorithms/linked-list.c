#include <stdint.h>
#include <stddef.h>

extern const int32_t printf(const int8_t* const format, ...);
extern const void* const malloc(const uint64_t size);
extern const void free(const void* const ptr);


struct Node {
  struct Node* left;
  struct Node* right;
  int32_t data;
};

static const void _ZJ0f10node__init61f1v3ptr43m40p37p34t4Node10m8p6t4Node10m8p6t4Node3m1i4data1i1p1p(struct Node** ptr, const int32_t data) {
  *ptr = malloc(20);
  struct Node* n = *ptr;
  n->data = data;
  n->left = NULL;
  n->right = NULL;
  return;
}

static const struct Node* const _ZJ0f12list__create42f37p34t4Node10m8p6t4Node10m8p6t4Node3m1i1p1p() {
  const struct Node* const n;
  _ZJ0f10node__init61f1v3ptr43m40p37p34t4Node10m8p6t4Node10m8p6t4Node3m1i4data1i1p1p(&n, 0);
  return n;
}

static const void _ZJ0f10list__free52f1v4head40m37p34t4Node10m8p6t4Node10m8p6t4Node3m1i1p1p(struct Node* head) {
  struct Node* current = head;
  struct Node* next = NULL;
  while (current != NULL) {
    next = current->right;
    free(current);
    current = next;
  }
}

static const void _ZJ0f12list__append59f1v4head40m37p34t4Node10m8p6t4Node10m8p6t4Node3m1i4data1i1p1p(struct Node* head, const int32_t data) {
  struct Node* n;
  _ZJ0f10node__init61f1v3ptr43m40p37p34t4Node10m8p6t4Node10m8p6t4Node3m1i4data1i1p1p(&n, data);
  struct Node* current = head;
  while (current->right != NULL) {
    current = current->right;
  }
  current->right = n;
  n->left = current;
  return;
}

static const void _ZJ0f12list__insert67f1v4head40m37p34t4Node10m8p6t4Node10m8p6t4Node3m1i4data1i5index1i1p1p(struct Node* head, const int32_t data, const int32_t index) {
  struct Node* n;
  _ZJ0f10node__init61f1v3ptr43m40p37p34t4Node10m8p6t4Node10m8p6t4Node3m1i4data1i1p1p(&n, data);
  struct Node* current = head;
  int32_t i = 0;
  while (current->right != NULL && i < index) {
    current = current->right;
    i += 1;
  }
  n->right = current->right;
  n->left = current;
  current->right = n;
  return;
}

static const void _ZJ0f13list__reverse55f1v4head43m40p37p34t4Node10m8p6t4Node10m8p6t4Node3m1i1p1p(struct Node** head) {
  struct Node* current = *head;
  struct Node* prev = NULL;
  struct Node* next = NULL;
  while (current != NULL) {
    next = current->right;
    current->right = prev;
    current->left = next;
    prev = current;
    current = next;
  }
  *head = prev;
}

static const void _ZJ0f11list__print52f1v4head40m37p34t4Node10m8p6t4Node10m8p6t4Node3m1i1p1p(struct Node* head) {
  struct Node* current = head;
  while (current != NULL) {
    printf("%d\n", current->data);
    current = current->right;
  }
  return;
}

__attribute__((visibility("default"))) const int32_t main() {
  const struct Node* const head = _ZJ0f12list__create42f37p34t4Node10m8p6t4Node10m8p6t4Node3m1i1p1p();
  _ZJ0f12list__append59f1v4head40m37p34t4Node10m8p6t4Node10m8p6t4Node3m1i4data1i1p1p(head, 1);
  _ZJ0f12list__append59f1v4head40m37p34t4Node10m8p6t4Node10m8p6t4Node3m1i4data1i1p1p(head, 2);
  _ZJ0f12list__append59f1v4head40m37p34t4Node10m8p6t4Node10m8p6t4Node3m1i4data1i1p1p(head, 3);
  _ZJ0f12list__insert67f1v4head40m37p34t4Node10m8p6t4Node10m8p6t4Node3m1i4data1i5index1i1p1p(head, 4, 1);
  _ZJ0f11list__print52f1v4head40m37p34t4Node10m8p6t4Node10m8p6t4Node3m1i1p1p(head);
  printf("Reversing list\n");
  _ZJ0f13list__reverse55f1v4head43m40p37p34t4Node10m8p6t4Node10m8p6t4Node3m1i1p1p(&head);
  _ZJ0f11list__print52f1v4head40m37p34t4Node10m8p6t4Node10m8p6t4Node3m1i1p1p(head);
  _ZJ0f10list__free52f1v4head40m37p34t4Node10m8p6t4Node10m8p6t4Node3m1i1p1p(head);
}
