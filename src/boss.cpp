class BossSD {
public:
	float lifeBar = 100.00;
	float speed = 0.4;
	float posInitialX;
	float posInitialY;

	Vector2 center = { (GetScreenWidth() - (GetScreenWidth() - posInitialX), GetScreenHeight() - (GetScreenHeight() - posInitialY)) };
;

	void movimentacaoBoss() {
		//movimentação apenas de seguir o inimigo
		posInitialX = posInitialX + (P.x / 4000);
		posInitialX = posInitialY + (P.y / 4000);
	}

	void comportamento() { //nessa função quero incluir todos os ataques do Boss de SD
		if (fabs(pow((P.x - posInitialX), 2) + pow((P.y - posInitialY), 2)) <= 400) {
			//distancia entre o player e o Boss de SD de 200 (ataque perto)
			DrawCircleSector(center, 300, 180, 30, 100.00, Fade(MAROON, 0.3f));
		}
	}
};
