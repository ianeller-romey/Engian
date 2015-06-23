using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

using TBGINTB_Builder.Extensions;
using TBGINTB_Builder.HelperControls;
using TBGINTB_Builder.Lib;


namespace TBGINTB_Builder.BuilderControls.Misc
{
    public class Window_RoomPreview : Window, IRegisterGinTubEventsOnlyWhenActive
    {
        #region MEMBER FIELDS
        #endregion


        #region MEMBER PROPERTIES

        public int? SelectedRoomId { get; private set; }

        #endregion


        #region MEMBER METHODS

        #region Public Functionality

        public Window_RoomPreview()
        {
        }

        public void SetActiveAndRegisterForGinTubEvents()
        {
            GinTubBuilderManager.RoomGet += GinTubBuilderManager_RoomGet;
        }

        public void SetInactiveAndUnregisterFromGinTubEvents()
        {
            GinTubBuilderManager.RoomGet -= GinTubBuilderManager_RoomGet;
        }

        #endregion


        #region Private Functionality

        void GinTubBuilderManager_RoomGet(object sender, GinTubBuilderManager.RoomGetEventArgs args)
        {
            throw new NotImplementedException();
        }

        #endregion

        #endregion
    }
}
