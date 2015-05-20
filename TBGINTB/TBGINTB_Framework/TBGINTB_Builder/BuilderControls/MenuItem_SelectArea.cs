using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

using TBGINTB_Builder.Lib;


namespace TBGINTB_Builder.BuilderControls
{
    public class MenuItem_SelectArea : MenuItem
    {
        #region MEMBER PROPERTIES

        public int AreaId { get; private set; }
        public string AreaName { get; private set; }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public MenuItem_SelectArea(int id, string name)
        {
            AreaId = id;
            SetAreaName(name);
            
            Click += MenuItem_SelectArea_Click;

            GinTubBuilderManager.AreaModified += GinTubBuilderManager_AreaModified;
        }

        #endregion


        #region PrivateFunctionality

        private void SetAreaName(string name)
        {
            AreaName = name;
            Header = AreaName;
        }

        private void MenuItem_SelectArea_Click(object sender, RoutedEventArgs e)
        {
            GinTubBuilderManager.GetArea(AreaId);
        }

        private void GinTubBuilderManager_AreaModified(object sender, GinTubBuilderManager.AreaModifiedEventArgs args)
        {
            if (args.Id == AreaId)
                SetAreaName(args.Name);
        }

        #endregion

        #endregion


    }
}
