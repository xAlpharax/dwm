/* appearance and colorscheme */
static const unsigned int borderpx  = 2;         /* border pixel of windows */
static const unsigned int snap      = 4;         /* snap pixel */
static const unsigned int gappx     = 4;         /* tiling spacing */
static const int showbar            = 1;         /* 0 means no bar */
static const int topbar             = 1;         /* 0 means bottom bar */
static const char *fonts[]          = { "inconsolata:pixelsize=17" };
static const char dmenufont[]       = "inconsolata:pixelsize=17";

static const char col_gray1[]       = "#0a001f"; // darkk purple
static const char col_gray2[]       = "#6660d2"; // light purple
static const char col_cyan[]        = "#ace6f0"; // light cyan

static const char *colors[][3]      = {
    /*               fg         bg         border   */
    [SchemeNorm] = { col_cyan,  col_gray1, col_gray2  }, // unselected
    [SchemeSel]  = { col_gray1, col_gray2, col_cyan   }, // selected
};

/* workspaces */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const char *alttags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
    /* xprop(1):
    *	WM_CLASS(STRING) = instance, class
    *	WM_NAME(STRING) = title
    */

    /* class      instance    title       tags mask     isfloating   monitor */
    { NULL,       NULL,       NULL,       0,            False,       -1 },

};

static const float mfact     = 0.5;  /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
    /* symbol     arrange */
    { "[]=",      tile },       /* first entry is default */
    { "><>",      NULL },       /* no layout function means floating behavior */
    { "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_cyan, "-sb", col_gray2, "-sf", col_gray1, NULL };
static const char *termcmd[]  = { "st", NULL };

#include "movestack.c"
static Key keys[] = {
    /* modifier                     key        function        argument */
    { MODKEY,                       XK_Return, spawn,          {.v = termcmd }      },
    { MODKEY,                       XK_p,      spawn,          {.v = dmenucmd }     },
    { MODKEY|ShiftMask,             XK_f,      spawn,          SHCMD("brave")       },
    { MODKEY,                       XK_f,      spawn,          SHCMD("firefox")     },
    { MODKEY|ShiftMask,             XK_l,      spawn,          SHCMD("librewolf")   },
    { MODKEY,                       XK_d,      spawn,          SHCMD("discord")     },
    { MODKEY|ShiftMask,             XK_x,      spawn,          SHCMD("xkill")       },
    { MODKEY|ShiftMask,             XK_b,      spawn,          SHCMD("bmenu")       },
    { MODKEY,                       XK_q,      spawn,          SHCMD("pmenu")       },

    { MODKEY,                       XK_Tab,    focusstack,     {.i = +1 } },

    { MODKEY,                       XK_b,      togglebar,      {0} },
    { MODKEY,                       XK_m,      togglefullscr,  {0} },
    { MODKEY,                       XK_x,      killclient,     {0} },

    { MODKEY,                       XK_k,      incnmaster,     {.i = +1 } },
    { MODKEY,                       XK_j,      incnmaster,     {.i = -1 } },
    { MODKEY|ShiftMask,             XK_k,      movestack,      {.i = +1 } },
    { MODKEY|ShiftMask,             XK_j,      movestack,      {.i = -1 } },

    { MODKEY,                       XK_h,      setmfact,       {.f = -0.01} },
    { MODKEY,                       XK_l,      setmfact,       {.f = +0.01} },

    { MODKEY,                       XK_space,  setlayout,      {.v = &layouts[0]} },
    { MODKEY|ShiftMask,             XK_space,  setlayout,      {.v = &layouts[1]} },
    { MODKEY|ControlMask,           XK_space,  setlayout,      {.v = &layouts[2]} },

    { MODKEY,                       XK_0,      view,           {.ui = ~0 } },

    { MODKEY,                       XK_Right,  viewnext,       {0} },
    { MODKEY,                       XK_Left,   viewprev,       {0} },

    TAGKEYS(                        XK_1,                      0)
    TAGKEYS(                        XK_2,                      1)
    TAGKEYS(                        XK_3,                      2)
    TAGKEYS(                        XK_4,                      3)
    TAGKEYS(                        XK_5,                      4)
    TAGKEYS(                        XK_6,                      5)
    TAGKEYS(                        XK_7,                      6)
    TAGKEYS(                        XK_8,                      7)
    TAGKEYS(                        XK_9,                      8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
