/* Teclas (app de fábrica de senew): probador del teclado. Pinta la matriz real del
 * W580i —6 columnas x 5 filas, una COLUMNA de la matriz por renglón de la rejilla— más el renglón de las cinco teclas a
 * masa, leída en crudo con ap_teclas_mapa() 25 veces por segundo; la celda pulsada (columna*5 + fila) se enciende.
 * Como hay que poder probar TODAS las teclas, se sale manteniendo «Atrás» un segundo. Mientras está abierta retiene las
 * teclas de música (ap_retener(W5_RET_TECLAS_MUSICA)): Walkman, Play y el volumen se PRUEBAN aquí, el sistema no se los
 * queda. Lo suelta al cerrarse y, si la app muere, el sistema al descargarla. */
#include "w5.h"
#include "w5_pantalla.h"                  /* (1.7) la letra nueva */

W5_APP(.api_menor = W5_PANT_MENOR, .nombre = "Teclas", .icono_gen = W5_IC_TECLAS, .version = 1, .caps = W5_CAP_TECLAS_CRUDAS);

static struct { u8 col[7], vistas[7]; int ultima, cuenta, atras; u32 version; } s;
static const char *const corto[35] = {       /* el orden de api/hw_comun.c (work/h2/teclas.tsv) */
    "3",   "6",   "1",   "",    "Wkm",
    "8",   "Sel D", "Atrás", "C", "Activ",
    "2",   "0",   "Sel I", "5",  "",
    "9",   "4",   "7",   "*",   "#",
    "",    "Vol-", "",   "Oper", "Vol+",
    "Aba.", "Izq.", "Arr.", "OK", "Der.",
    "Enc.", "Rebo", "Avan", "Alt", "Play" };

static void sondeo(W5Ctx c)
{
    u8 col[7]; int f, k, cambio = 0;
    memset(col, 0, sizeof col);
    ap_teclas_mapa(col);
    for (f = 0; f < 7; f++) {
        u8 nuevas = (u8)(col[f] & ~s.col[f]);
        for (k = 0; k < 5; k++) if (nuevas & (1u << k)) { s.ultima = f * 5 + k; s.cuenta++; }
        if (col[f] != s.col[f]) cambio = 1;
        s.vistas[f] |= col[f]; s.col[f] = col[f];
    }
    s.atras = ap_tecla_abajo(W5K_ATRAS) ? s.atras + 1 : 0;
    if (s.atras >= 25) { ap_salir(); return; }
    if (cambio) { s.version++; ui_sucio(c); }
}
static void iniciar(W5Ctx c, void *dato)
{
    (void)dato;
    memset(&s, 0, sizeof s);
    s.ultima = -1;
    ui_cada(c, 40, sondeo);
    ap_retener(W5_RET_TECLAS_MUSICA, 1);       /* aquí Walkman, Play y el volumen se PRUEBAN: el sistema no se los queda */
}
static void desechar(W5Ctx c, void *dato) { (void)c; (void)dato; ap_retener(W5_RET_TECLAS_MUSICA, 0); }
static int tecla(W5Ctx t, int k, void *dato) { (void)t; (void)k; (void)dato; return 1; }     /* todas se quedan aquí */
static void pintar(W5Lienzo l, const W5Rect *rr, void *dato)
{
    W5Rect r = *rr;
    unsigned barra = ui_color(W5_COL_BARRA), acento = ui_color(W5_COL_ACENTO), texto = ui_color(W5_COL_TEXTO), sobre = ui_color(W5_COL_SOBRE_ACENTO);
    int f, k, cw = (r.w - 4) / 5, ch = (r.h - 2) / 7;
    (void)dato;
    for (f = 0; f < 7; f++) for (k = 0; k < 5; k++) {
        int x = r.x + 2 + k * cw, y = r.y + 1 + f * ch, on = (s.col[f] >> k) & 1, vista = (s.vistas[f] >> k) & 1;
        const char *n = corto[f * 5 + k];
        if (!n[0]) { li_marco(l, x + 1, y + 1, cw - 2, ch - 2, barra); continue; }
        li_rect(l, x + 1, y + 1, cw - 2, ch - 2, on ? acento : barra);
        if (vista && !on) li_rect(l, x + 1, y + ch - 3, cw - 2, 2, acento);   /* ya probada: subrayada */
        {   /* (1.7) en la talla pequeña y centrada con su alto de verdad (antes daba por hecho 7 px) */
            const int pq = W5_F_ESTILO(W5_T_PEQUENA);
            li_texto(l, x + (cw - li_ancho_texto(n, 1, pq)) / 2, y + (ch - ui_alto_texto(1, pq)) / 2, n, on ? sobre : texto, 1, pq);
        }
    }
}
static W5W construir(W5Ctx c, void *dato)
{
    unsigned tenue = ui_color(W5_COL_TENUE);
    int f, k, probadas = 0;
    char nombre[24];
    (void)c; (void)dato;
    for (f = 0; f < 7; f++) for (k = 0; k < 5; k++) if ((s.vistas[f] >> k) & 1) probadas++;
    nombre[0] = 0;
    if (s.ultima >= 0) ap_celda_nombre(s.ultima, nombre, sizeof nombre);
    return Teclas(tecla, ui_andamio("Teclas", Columna(A_CRUZADO(W5P_ESTIRAR), HIJOS(
        RellenoXY(4, 3, Fila(HIJOS(
            Texto(s.ultima >= 0 ? ui_fmt("%s (celda %d: col. %d, fila %d)", nombre, s.ultima, s.ultima / 5, s.ultima % 5) : "Pulsa cualquier tecla", A_COLOR(ui_color(W5_COL_ACENTO)), A_MARCAS(W5_F_ESTILO(W5_T_PEQUENA)))))),
        Expandido(Pintura(pintar, A_VERSION(s.version))),
        RellenoXY(4, 2, Texto(ui_fmt("%d pulsaciones · %d/31 probadas", s.cuenta, probadas), A_COLOR(tenue), A_MARCAS(W5_F_ESTILO(W5_T_PEQUENA)))))),
        "7 = masa", "mantén Atrás"));
}
W5Pal app_suceso(int suceso, W5Pal a, W5Pal b)
{
    (void)a; (void)b;
    if (suceso == W5_ABRIR) return (W5Pal)ui_pantalla(construir, iniciar, desechar, NULL);
    return 0;
}
