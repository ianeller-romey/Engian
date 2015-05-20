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

using TBGINTB_Builder.BuilderControls;
using TBGINTB_Builder.HelperControls;
using TBGINTB_Builder.Extensions;
using TBGINTB_Builder.Lib;


namespace TBGINTB_Builder
{
    public partial class MainWindow : Window
    {
        #region MEMBER FIELDS

        TabControl m_tabControl_controls;
        MenuItem m_menuItem_selectArea;

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public MainWindow()
        {
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
            m_tabControl_controls = new TabControl();
            m_tabControl_controls.Items.Add(new TabItem_Area());
            m_tabControl_controls.Items.Add(new TabItem_Locations());

            ////////
            // grid
            Grid grid_main = new Grid();
            grid_main.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            grid_main.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(100.0, GridUnitType.Star) });
            grid_main.SetGridRowColumn(dockPanel_main, 0, 0);
            grid_main.SetGridRowColumn(m_tabControl_controls, 1, 0);

            return grid_main;
        }

        private void CreateGinTubManager()
        {
            GinTubBuilderManager.Initialize();
            GinTubBuilderManager.AreaAdded += GinTubBuilderManager_AreaAdded;

            GinTubBuilderManager.LoadAllAreas();
            GinTubBuilderManager.LoadAllLocations();
        }

        private void AddArea(object sender, RoutedEventArgs e)
        {
            Window_TextEntry window = new Window_TextEntry("Area Name", "");
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
