
// Math
#include "mathTrig.h"

// std
#include <cmath>


namespace Math
{

    namespace {

        float g_sinTable[360] = {
            sinf(0),   sinf(1),   sinf(2),   sinf(3),   sinf(4),   sinf(5),   sinf(6),   sinf(7),   sinf(8),   sinf(9),
            sinf(10),  sinf(11),  sinf(12),  sinf(13),  sinf(14),  sinf(15),  sinf(16),  sinf(17),  sinf(18),  sinf(19),
            sinf(20),  sinf(21),  sinf(22),  sinf(23),  sinf(24),  sinf(25),  sinf(26),  sinf(27),  sinf(28),  sinf(29),
            sinf(30),  sinf(31),  sinf(32),  sinf(33),  sinf(34),  sinf(35),  sinf(36),  sinf(37),  sinf(38),  sinf(39),
            sinf(40),  sinf(41),  sinf(42),  sinf(43),  sinf(44),  sinf(45),  sinf(46),  sinf(47),  sinf(48),  sinf(49),
            sinf(50),  sinf(51),  sinf(52),  sinf(53),  sinf(54),  sinf(55),  sinf(56),  sinf(57),  sinf(58),  sinf(59),
            sinf(60),  sinf(61),  sinf(62),  sinf(63),  sinf(64),  sinf(65),  sinf(66),  sinf(67),  sinf(68),  sinf(69),
            sinf(70),  sinf(71),  sinf(72),  sinf(73),  sinf(74),  sinf(75),  sinf(76),  sinf(77),  sinf(78),  sinf(79),
            sinf(80),  sinf(81),  sinf(82),  sinf(83),  sinf(84),  sinf(85),  sinf(86),  sinf(87),  sinf(88),  sinf(89),
            sinf(90),  sinf(91),  sinf(92),  sinf(93),  sinf(94),  sinf(95),  sinf(96),  sinf(97),  sinf(98),  sinf(99),
            sinf(100), sinf(101), sinf(102), sinf(103), sinf(104), sinf(105), sinf(106), sinf(107), sinf(108), sinf(109),
            sinf(110), sinf(111), sinf(112), sinf(113), sinf(114), sinf(115), sinf(116), sinf(117), sinf(118), sinf(119),
            sinf(120), sinf(121), sinf(122), sinf(123), sinf(124), sinf(125), sinf(126), sinf(127), sinf(128), sinf(129),
            sinf(130), sinf(131), sinf(132), sinf(133), sinf(134), sinf(135), sinf(136), sinf(137), sinf(138), sinf(139),
            sinf(140), sinf(141), sinf(142), sinf(143), sinf(144), sinf(145), sinf(146), sinf(147), sinf(148), sinf(149),
            sinf(150), sinf(151), sinf(152), sinf(153), sinf(154), sinf(155), sinf(156), sinf(157), sinf(158), sinf(159),
            sinf(160), sinf(161), sinf(162), sinf(163), sinf(164), sinf(165), sinf(166), sinf(167), sinf(168), sinf(169),
            sinf(170), sinf(171), sinf(172), sinf(173), sinf(174), sinf(175), sinf(176), sinf(177), sinf(178), sinf(179),
            sinf(180), sinf(181), sinf(182), sinf(183), sinf(184), sinf(185), sinf(186), sinf(187), sinf(188), sinf(189),
            sinf(190), sinf(191), sinf(192), sinf(193), sinf(194), sinf(195), sinf(196), sinf(197), sinf(198), sinf(199),
            sinf(200), sinf(201), sinf(202), sinf(203), sinf(204), sinf(205), sinf(206), sinf(207), sinf(208), sinf(209),
            sinf(210), sinf(211), sinf(212), sinf(213), sinf(214), sinf(215), sinf(216), sinf(217), sinf(218), sinf(219),
            sinf(220), sinf(221), sinf(222), sinf(223), sinf(224), sinf(225), sinf(226), sinf(227), sinf(228), sinf(229),
            sinf(230), sinf(231), sinf(232), sinf(233), sinf(234), sinf(235), sinf(236), sinf(237), sinf(238), sinf(239),
            sinf(240), sinf(241), sinf(242), sinf(243), sinf(244), sinf(245), sinf(246), sinf(247), sinf(248), sinf(249),
            sinf(250), sinf(251), sinf(252), sinf(253), sinf(254), sinf(255), sinf(256), sinf(257), sinf(258), sinf(259),
            sinf(260), sinf(261), sinf(262), sinf(263), sinf(264), sinf(265), sinf(266), sinf(267), sinf(268), sinf(269),
            sinf(270), sinf(271), sinf(272), sinf(273), sinf(274), sinf(275), sinf(276), sinf(277), sinf(278), sinf(279),
            sinf(280), sinf(281), sinf(282), sinf(283), sinf(284), sinf(285), sinf(286), sinf(287), sinf(288), sinf(289),
            sinf(290), sinf(291), sinf(292), sinf(293), sinf(294), sinf(295), sinf(296), sinf(297), sinf(298), sinf(299),
            sinf(300), sinf(301), sinf(302), sinf(303), sinf(304), sinf(305), sinf(306), sinf(307), sinf(308), sinf(309),
            sinf(310), sinf(311), sinf(312), sinf(313), sinf(314), sinf(315), sinf(316), sinf(317), sinf(318), sinf(319),
            sinf(320), sinf(321), sinf(322), sinf(323), sinf(324), sinf(325), sinf(326), sinf(327), sinf(328), sinf(329),
            sinf(330), sinf(331), sinf(332), sinf(333), sinf(334), sinf(335), sinf(336), sinf(337), sinf(338), sinf(339),
            sinf(340), sinf(341), sinf(342), sinf(343), sinf(344), sinf(345), sinf(346), sinf(347), sinf(348), sinf(349),
            sinf(350), sinf(351), sinf(352), sinf(353), sinf(354), sinf(355), sinf(356), sinf(357), sinf(358), sinf(359)
        };


        float g_cosTable[360] = {
            cosf(0),   cosf(1),   cosf(2),   cosf(3),   cosf(4),   cosf(5),   cosf(6),   cosf(7),   cosf(8),   cosf(9),
            cosf(10),  cosf(11),  cosf(12),  cosf(13),  cosf(14),  cosf(15),  cosf(16),  cosf(17),  cosf(18),  cosf(19),
            cosf(20),  cosf(21),  cosf(22),  cosf(23),  cosf(24),  cosf(25),  cosf(26),  cosf(27),  cosf(28),  cosf(29),
            cosf(30),  cosf(31),  cosf(32),  cosf(33),  cosf(34),  cosf(35),  cosf(36),  cosf(37),  cosf(38),  cosf(39),
            cosf(40),  cosf(41),  cosf(42),  cosf(43),  cosf(44),  cosf(45),  cosf(46),  cosf(47),  cosf(48),  cosf(49),
            cosf(50),  cosf(51),  cosf(52),  cosf(53),  cosf(54),  cosf(55),  cosf(56),  cosf(57),  cosf(58),  cosf(59),
            cosf(60),  cosf(61),  cosf(62),  cosf(63),  cosf(64),  cosf(65),  cosf(66),  cosf(67),  cosf(68),  cosf(69),
            cosf(70),  cosf(71),  cosf(72),  cosf(73),  cosf(74),  cosf(75),  cosf(76),  cosf(77),  cosf(78),  cosf(79),
            cosf(80),  cosf(81),  cosf(82),  cosf(83),  cosf(84),  cosf(85),  cosf(86),  cosf(87),  cosf(88),  cosf(89),
            cosf(90),  cosf(91),  cosf(92),  cosf(93),  cosf(94),  cosf(95),  cosf(96),  cosf(97),  cosf(98),  cosf(99),
            cosf(100), cosf(101), cosf(102), cosf(103), cosf(104), cosf(105), cosf(106), cosf(107), cosf(108), cosf(109),
            cosf(110), cosf(111), cosf(112), cosf(113), cosf(114), cosf(115), cosf(116), cosf(117), cosf(118), cosf(119),
            cosf(120), cosf(121), cosf(122), cosf(123), cosf(124), cosf(125), cosf(126), cosf(127), cosf(128), cosf(129),
            cosf(130), cosf(131), cosf(132), cosf(133), cosf(134), cosf(135), cosf(136), cosf(137), cosf(138), cosf(139),
            cosf(140), cosf(141), cosf(142), cosf(143), cosf(144), cosf(145), cosf(146), cosf(147), cosf(148), cosf(149),
            cosf(150), cosf(151), cosf(152), cosf(153), cosf(154), cosf(155), cosf(156), cosf(157), cosf(158), cosf(159),
            cosf(160), cosf(161), cosf(162), cosf(163), cosf(164), cosf(165), cosf(166), cosf(167), cosf(168), cosf(169),
            cosf(170), cosf(171), cosf(172), cosf(173), cosf(174), cosf(175), cosf(176), cosf(177), cosf(178), cosf(179),
            cosf(180), cosf(181), cosf(182), cosf(183), cosf(184), cosf(185), cosf(186), cosf(187), cosf(188), cosf(189),
            cosf(190), cosf(191), cosf(192), cosf(193), cosf(194), cosf(195), cosf(196), cosf(197), cosf(198), cosf(199),
            cosf(200), cosf(201), cosf(202), cosf(203), cosf(204), cosf(205), cosf(206), cosf(207), cosf(208), cosf(209),
            cosf(210), cosf(211), cosf(212), cosf(213), cosf(214), cosf(215), cosf(216), cosf(217), cosf(218), cosf(219),
            cosf(220), cosf(221), cosf(222), cosf(223), cosf(224), cosf(225), cosf(226), cosf(227), cosf(228), cosf(229),
            cosf(230), cosf(231), cosf(232), cosf(233), cosf(234), cosf(235), cosf(236), cosf(237), cosf(238), cosf(239),
            cosf(240), cosf(241), cosf(242), cosf(243), cosf(244), cosf(245), cosf(246), cosf(247), cosf(248), cosf(249),
            cosf(250), cosf(251), cosf(252), cosf(253), cosf(254), cosf(255), cosf(256), cosf(257), cosf(258), cosf(259),
            cosf(260), cosf(261), cosf(262), cosf(263), cosf(264), cosf(265), cosf(266), cosf(267), cosf(268), cosf(269),
            cosf(270), cosf(271), cosf(272), cosf(273), cosf(274), cosf(275), cosf(276), cosf(277), cosf(278), cosf(279),
            cosf(280), cosf(281), cosf(282), cosf(283), cosf(284), cosf(285), cosf(286), cosf(287), cosf(288), cosf(289),
            cosf(290), cosf(291), cosf(292), cosf(293), cosf(294), cosf(295), cosf(296), cosf(297), cosf(298), cosf(299),
            cosf(300), cosf(301), cosf(302), cosf(303), cosf(304), cosf(305), cosf(306), cosf(307), cosf(308), cosf(309),
            cosf(310), cosf(311), cosf(312), cosf(313), cosf(314), cosf(315), cosf(316), cosf(317), cosf(318), cosf(319),
            cosf(320), cosf(321), cosf(322), cosf(323), cosf(324), cosf(325), cosf(326), cosf(327), cosf(328), cosf(329),
            cosf(330), cosf(331), cosf(332), cosf(333), cosf(334), cosf(335), cosf(336), cosf(337), cosf(338), cosf(339),
            cosf(340), cosf(341), cosf(342), cosf(343), cosf(344), cosf(345), cosf(346), cosf(347), cosf(348), cosf(349),
            cosf(350), cosf(351), cosf(352), cosf(353), cosf(354), cosf(355), cosf(356), cosf(357), cosf(358), cosf(359)
        };

    }


    float Sine(const float value)
    {
        return g_sinTable[(int)value];
    }


    float Cosine(const float value)
    {
        return g_cosTable[(int)value];
    }

}