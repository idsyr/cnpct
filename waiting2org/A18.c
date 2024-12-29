// Семинар 5.3. Динамическое программирование
// Принцип оптимальности Беллмана
// Функциональное уравнение Беллмана

// An optimal policy has the property that whatever the initial
// state and initial decision are, the remaining decisions
// must constitude an optimal policy with regard to the state
// resulting from the first decision

// Изменение состояния xt->xt+1 = T(xt, at) with payoff F(xt, at)
// V(x0) = max(a0...at)(sum(t)_for(F(xt, at))
// THEN V(xt) = max(at)[ F(xt, at) + V(xt, at) ]

// xt+1 = xt-at
// F(xt,at) = 1
// at |=- {c1...ck}
// v(n) = min(V(n-c1), V(n-c2) ... V(n-ck)) + 1

// Восходящее и нисходящее решение
int min(int a, int b);
#define INT_MAX 2147483647
int calc_change(int n, int m, int *changes, int *V){
	int i;
	if(n==0) return 0;
	if(n <0) return INT_MAX;
	if(V[n] != INT_MAX) return V[n];
	for(i = 0; i<m; ++i){
		int CT = calc_change(n - changes[i], m, changes, V);
		if(CT == INT_MAX) continue;
		V[n] = min(V[n], CT + 1); // (!)
	}
	return V[n];
}

// 40:40

// Грамматика состоит из продукций
// Нетерминальные символы  -->  нетерминальные / терминальные
// Грамматику можно распознать с помощью динамического прграммирования
// Нормальная грамматика Хомского
// Алгоритм Кока-Янгера-Кaсами
// Контекстно свободная грамматика - слева один нетерминал 
