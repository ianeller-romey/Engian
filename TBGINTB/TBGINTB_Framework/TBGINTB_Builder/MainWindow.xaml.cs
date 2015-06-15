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

        Grid m_grid_main;
        TabControl m_tabControl_controls;

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public MainWindow()
        {
            InitializeComponent();
            Content = CreateControls();
            CreateGinTubManager();
            Width = 1000;
            Height = 500;
        }

        #endregion


        #region Private Functionality

        private UIElement CreateControls()
        {
            ////////
            // toolbar
            MenuItem menuItem_loadFromDatabase = new MenuItem() { Header = "Load DB" };
            menuItem_loadFromDatabase.Click += MenuItem_LoadFromDatabase_Click;

            MenuItem menuItem_file = new MenuItem() { Header = "File" };
            menuItem_file.Items.Add(menuItem_loadFromDatabase);

            Menu menu_main = new Menu();
            menu_main.Items.Add(menuItem_file);

            DockPanel dockPanel_main = new DockPanel();
            dockPanel_main.Children.Add(menu_main);
            DockPanel.SetDock(menu_main, Dock.Top);

            ////////
            // grid
            m_grid_main = new Grid();
            m_grid_main.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            m_grid_main.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(100.0, GridUnitType.Star) });
            m_grid_main.SetGridRowColumn(dockPanel_main, 0, 0);

            return m_grid_main;
        }

        private void CreateControlsAfterLoading()
        {
            ////////
            // tab control
            m_tabControl_controls = new TabControl();
            m_tabControl_controls.Items.Add(new TabItem_Area());
            m_tabControl_controls.Items.Add(new TabItem_Locations());
            m_tabControl_controls.Items.Add(new TabItem_Verbs());
            m_tabControl_controls.Items.Add(new TabItem_Results());
            m_tabControl_controls.Items.Add(new TabItem_Items());
            m_tabControl_controls.Items.Add(new TabItem_Events());
            m_tabControl_controls.Items.Add(new TabItem_Characters());
            m_tabControl_controls.Items.Add(new TabItem_Messages());

            ////////
            // grid
            m_grid_main.SetGridRowColumn(m_tabControl_controls, 1, 0);
        }

        private void CreateGinTubManager()
        {
            GinTubBuilderManager.Initialize();
        }

        private void MenuItem_LoadFromDatabase_Click(object sender, RoutedEventArgs e)
        {
            MenuItem menuItem = sender as MenuItem;
            if(menuItem != null)
            {
                CreateControlsAfterLoading();
                CreateGinTubManager();
                m_tabControl_controls.SelectionChanged += TabControl_Controls_SelectionChanged;
                m_tabControl_controls.SelectedItem = m_tabControl_controls.Items.OfType<TabItem>().First();

                menuItem.Click -= MenuItem_LoadFromDatabase_Click;
            }
        }

        void TabControl_Controls_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (e.OriginalSource != m_tabControl_controls)
                return;

            foreach (var i in m_tabControl_controls.Items.OfType<IRegisterGinTubEventsOnlyWhenActive>())
                i.SetInactiveAndUnregisterFromGinTubEvents();
            var item = (m_tabControl_controls.SelectedItem as IRegisterGinTubEventsOnlyWhenActive);
            if (item != null)
                item.SetActiveAndRegisterForGinTubEvents();
        }

        #endregion

        #endregion
    }
}
