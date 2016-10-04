
// Math
#include "mathTrig.h"

// std
#include <cmath>


namespace Math
{

    namespace {

        float g_sinTable[360] = {
            sin(0),   sin(1),   sin(2),   sin(3),   sin(4),   sin(5),   sin(6),   sin(7),   sin(8),   sin(9),
            sin(10),  sin(11),  sin(12),  sin(13),  sin(14),  sin(15),  sin(16),  sin(17),  sin(18),  sin(19),
            sin(20),  sin(21),  sin(22),  sin(23),  sin(24),  sin(25),  sin(26),  sin(27),  sin(28),  sin(29),
            sin(30),  sin(31),  sin(32),  sin(33),  sin(34),  sin(35),  sin(36),  sin(37),  sin(38),  sin(39),
            sin(40),  sin(41),  sin(42),  sin(43),  sin(44),  sin(45),  sin(46),  sin(47),  sin(48),  sin(49),
            sin(50),  sin(51),  sin(52),  sin(53),  sin(54),  sin(55),  sin(56),  sin(57),  sin(58),  sin(59),
            sin(60),  sin(61),  sin(62),  sin(63),  sin(64),  sin(65),  sin(66),  sin(67),  sin(68),  sin(69),
            sin(70),  sin(71),  sin(72),  sin(73),  sin(74),  sin(75),  sin(76),  sin(77),  sin(78),  sin(79),
            sin(80),  sin(81),  sin(82),  sin(83),  sin(84),  sin(85),  sin(86),  sin(87),  sin(88),  sin(89),
            sin(90),  sin(91),  sin(92),  sin(93),  sin(94),  sin(95),  sin(96),  sin(97),  sin(98),  sin(99),
            sin(100), sin(101), sin(102), sin(103), sin(104), sin(105), sin(106), sin(107), sin(108), sin(109),
            sin(110), sin(111), sin(112), sin(113), sin(114), sin(115), sin(116), sin(117), sin(118), sin(119),
            sin(120), sin(121), sin(122), sin(123), sin(124), sin(125), sin(126), sin(127), sin(128), sin(129),
            sin(130), sin(131), sin(132), sin(133), sin(134), sin(135), sin(136), sin(137), sin(138), sin(139),
            sin(140), sin(141), sin(142), sin(143), sin(144), sin(145), sin(146), sin(147), sin(148), sin(149),
            sin(150), sin(151), sin(152), sin(153), sin(154), sin(155), sin(156), sin(157), sin(158), sin(159),
            sin(160), sin(161), sin(162), sin(163), sin(164), sin(165), sin(166), sin(167), sin(168), sin(169),
            sin(170), sin(171), sin(172), sin(173), sin(174), sin(175), sin(176), sin(177), sin(178), sin(179),
            sin(180), sin(181), sin(182), sin(183), sin(184), sin(185), sin(186), sin(187), sin(188), sin(189),
            sin(190), sin(191), sin(192), sin(193), sin(194), sin(195), sin(196), sin(197), sin(198), sin(199),
            sin(200), sin(201), sin(202), sin(203), sin(204), sin(205), sin(206), sin(207), sin(208), sin(209),
            sin(210), sin(211), sin(212), sin(213), sin(214), sin(215), sin(216), sin(217), sin(218), sin(219),
            sin(220), sin(221), sin(222), sin(223), sin(224), sin(225), sin(226), sin(227), sin(228), sin(229),
            sin(230), sin(231), sin(232), sin(233), sin(234), sin(235), sin(236), sin(237), sin(238), sin(239),
            sin(240), sin(241), sin(242), sin(243), sin(244), sin(245), sin(246), sin(247), sin(248), sin(249),
            sin(250), sin(251), sin(252), sin(253), sin(254), sin(255), sin(256), sin(257), sin(258), sin(259),
            sin(260), sin(261), sin(262), sin(263), sin(264), sin(265), sin(266), sin(267), sin(268), sin(269),
            sin(270), sin(271), sin(272), sin(273), sin(274), sin(275), sin(276), sin(277), sin(278), sin(279),
            sin(280), sin(281), sin(282), sin(283), sin(284), sin(285), sin(286), sin(287), sin(288), sin(289),
            sin(290), sin(291), sin(292), sin(293), sin(294), sin(295), sin(296), sin(297), sin(298), sin(299),
            sin(300), sin(301), sin(302), sin(303), sin(304), sin(305), sin(306), sin(307), sin(308), sin(309),
            sin(310), sin(311), sin(312), sin(313), sin(314), sin(315), sin(316), sin(317), sin(318), sin(319),
            sin(320), sin(321), sin(322), sin(323), sin(324), sin(325), sin(326), sin(327), sin(328), sin(329),
            sin(330), sin(331), sin(332), sin(333), sin(334), sin(335), sin(336), sin(337), sin(338), sin(339),
            sin(340), sin(341), sin(342), sin(343), sin(344), sin(345), sin(346), sin(347), sin(348), sin(349),
            sin(350), sin(351), sin(352), sin(353), sin(354), sin(355), sin(356), sin(357), sin(358), sin(359)
        };


        float g_cosTable[360] = {
            cos(0),   cos(1),   cos(2),   cos(3),   cos(4),   cos(5),   cos(6),   cos(7),   cos(8),   cos(9),
            cos(10),  cos(11),  cos(12),  cos(13),  cos(14),  cos(15),  cos(16),  cos(17),  cos(18),  cos(19),
            cos(20),  cos(21),  cos(22),  cos(23),  cos(24),  cos(25),  cos(26),  cos(27),  cos(28),  cos(29),
            cos(30),  cos(31),  cos(32),  cos(33),  cos(34),  cos(35),  cos(36),  cos(37),  cos(38),  cos(39),
            cos(40),  cos(41),  cos(42),  cos(43),  cos(44),  cos(45),  cos(46),  cos(47),  cos(48),  cos(49),
            cos(50),  cos(51),  cos(52),  cos(53),  cos(54),  cos(55),  cos(56),  cos(57),  cos(58),  cos(59),
            cos(60),  cos(61),  cos(62),  cos(63),  cos(64),  cos(65),  cos(66),  cos(67),  cos(68),  cos(69),
            cos(70),  cos(71),  cos(72),  cos(73),  cos(74),  cos(75),  cos(76),  cos(77),  cos(78),  cos(79),
            cos(80),  cos(81),  cos(82),  cos(83),  cos(84),  cos(85),  cos(86),  cos(87),  cos(88),  cos(89),
            cos(90),  cos(91),  cos(92),  cos(93),  cos(94),  cos(95),  cos(96),  cos(97),  cos(98),  cos(99),
            cos(100), cos(101), cos(102), cos(103), cos(104), cos(105), cos(106), cos(107), cos(108), cos(109),
            cos(110), cos(111), cos(112), cos(113), cos(114), cos(115), cos(116), cos(117), cos(118), cos(119),
            cos(120), cos(121), cos(122), cos(123), cos(124), cos(125), cos(126), cos(127), cos(128), cos(129),
            cos(130), cos(131), cos(132), cos(133), cos(134), cos(135), cos(136), cos(137), cos(138), cos(139),
            cos(140), cos(141), cos(142), cos(143), cos(144), cos(145), cos(146), cos(147), cos(148), cos(149),
            cos(150), cos(151), cos(152), cos(153), cos(154), cos(155), cos(156), cos(157), cos(158), cos(159),
            cos(160), cos(161), cos(162), cos(163), cos(164), cos(165), cos(166), cos(167), cos(168), cos(169),
            cos(170), cos(171), cos(172), cos(173), cos(174), cos(175), cos(176), cos(177), cos(178), cos(179),
            cos(180), cos(181), cos(182), cos(183), cos(184), cos(185), cos(186), cos(187), cos(188), cos(189),
            cos(190), cos(191), cos(192), cos(193), cos(194), cos(195), cos(196), cos(197), cos(198), cos(199),
            cos(200), cos(201), cos(202), cos(203), cos(204), cos(205), cos(206), cos(207), cos(208), cos(209),
            cos(210), cos(211), cos(212), cos(213), cos(214), cos(215), cos(216), cos(217), cos(218), cos(219),
            cos(220), cos(221), cos(222), cos(223), cos(224), cos(225), cos(226), cos(227), cos(228), cos(229),
            cos(230), cos(231), cos(232), cos(233), cos(234), cos(235), cos(236), cos(237), cos(238), cos(239),
            cos(240), cos(241), cos(242), cos(243), cos(244), cos(245), cos(246), cos(247), cos(248), cos(249),
            cos(250), cos(251), cos(252), cos(253), cos(254), cos(255), cos(256), cos(257), cos(258), cos(259),
            cos(260), cos(261), cos(262), cos(263), cos(264), cos(265), cos(266), cos(267), cos(268), cos(269),
            cos(270), cos(271), cos(272), cos(273), cos(274), cos(275), cos(276), cos(277), cos(278), cos(279),
            cos(280), cos(281), cos(282), cos(283), cos(284), cos(285), cos(286), cos(287), cos(288), cos(289),
            cos(290), cos(291), cos(292), cos(293), cos(294), cos(295), cos(296), cos(297), cos(298), cos(299),
            cos(300), cos(301), cos(302), cos(303), cos(304), cos(305), cos(306), cos(307), cos(308), cos(309),
            cos(310), cos(311), cos(312), cos(313), cos(314), cos(315), cos(316), cos(317), cos(318), cos(319),
            cos(320), cos(321), cos(322), cos(323), cos(324), cos(325), cos(326), cos(327), cos(328), cos(329),
            cos(330), cos(331), cos(332), cos(333), cos(334), cos(335), cos(336), cos(337), cos(338), cos(339),
            cos(340), cos(341), cos(342), cos(343), cos(344), cos(345), cos(346), cos(347), cos(348), cos(349),
            cos(350), cos(351), cos(352), cos(353), cos(354), cos(355), cos(356), cos(357), cos(358), cos(359)
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