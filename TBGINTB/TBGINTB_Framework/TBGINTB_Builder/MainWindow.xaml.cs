using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

using TBGINTB_Builder.Controls;
using TBGINTB_Builder.Lib;

using IANWork;


namespace TBGINTB_Builder
{
    public partial class MainWindow : Window
    {
        #region MEMBER FIELDS

        TabControl m_tabControl_areas;
        MenuItem m_menuItem_selectArea;

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public MainWindow()
        {
            IW.Init(IW.DefaultTextBoxWidth, IW.DefaultButtonWidth, IW.DefaultComboBoxWidth, Brushes.Gray, Brushes.Black);
            InitializeComponent();
            Content = CreateControls();
            CreateGinTubManager();
        }

        #endregion


        #region Private Functionality

        private UIElement CreateControls()
        {
            ////////
            // toolbar
            MenuItem menuItem_addArea = new MenuItem() { Header = "Add Area" };
            menuItem_addArea.Click += AddArea;

            m_menuItem_selectArea = new MenuItem() { Header = "Select Area" }; 

            MenuItem menuItem_areas = new MenuItem() { Header = "Areas" };
            menuItem_areas.Items.Add(menuItem_addArea);
            menuItem_areas.Items.Add(m_menuItem_selectArea);

            Menu menu_main = new Menu();
            menu_main.Items.Add(menuItem_areas);

            DockPanel dockPanel_main = new DockPanel();
            dockPanel_main.Children.Add(menu_main);
            DockPanel.SetDock(menu_main, Dock.Top);

            ////////
            // tab control
            m_tabControl_areas = new TabControl();
            m_tabControl_areas.Items.Add(new TabItem_Area());

            ////////
            // grid
            Grid grid_main = new Grid();
            grid_main.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            grid_main.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(100.0, GridUnitType.Star) });
            IW.SetGridRowColumn(grid_main, dockPanel_main, 0, -1);
            IW.SetGridRowColumn(grid_main, m_tabControl_areas, 1, -1);

            return grid_main;
        }

        private void CreateGinTubManager()
        {
            GinTubBuilderManager.Initialize();
            GinTubBuilderManager.AreaAdded += GinTubBuilderManager_AreaAdded;

            GinTubBuilderManager.LoadAllAreas();
        }

        private void AddArea(object sender, RoutedEventArgs e)
        {
            Window_TextBoxEntry window = new Window_TextBoxEntry("Area name", "");
            window.ShowDialog();
            if (window.Accepted)
                GinTubBuilderManager.AddArea(window.Text);
        }

        private void GinTubBuilderManager_AreaAdded(object sender, GinTubBuilderManager.AreaAddedEventArgs args)
        {
            MenuItem_SelectArea menuItem_area = new MenuItem_SelectArea(args.Id, args.Name);

            m_menuItem_selectArea.Items.Add(menuItem_area);
        }

        #endregion

        #endregion
    }
}
