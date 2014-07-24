# ============================================================================
#
#                       Provisioning Manager
#
#@author: Sami Utriainen
# ============================================================================

import clr, os
clr.AddReference('System.Web.Extensions')
clr.AddReference('MessageAPI.MultiSim')
clr.AddReference('Nokia.Trident.Phone')

from System.Web.Script.Serialization import JavaScriptSerializer
from Nokia.RD.MessageAPI.MultiSim.Messages import MultiSimInfoGetReq, MultiSimInfoSetReq_002_000
from Nokia.RD.MessageAPI.MultiSim.Subblocks import MultiSimSbFlags
from Nokia.RD.MessageAPI.MultiSim.Tables import MultiSimInfo, MultiSimInfoSbFlags, MultiSimSetAction
from Nokia.RD.CoreTestTool import ConnectionManager

from interfaces import srv_granite
import core
from core import uitestcase, debug
from core.testcase_exceptions import TestException

from System import String, Array, Byte
from System.Text import Encoding
from System.IO import File, FileInfo
from System.Collections.Generic import Dictionary

import wbxml2json

class ProvisioningManager(object):
    """Class for managing provisioning data in device"""

    def __init__(self):
        self.encoding = Encoding.Default
        self.serializer = None
        self.sx = None
    
    def getSimCount(self, phone):
        """Gets amount of sim cards inserted in device. In case of 1 SIM card inserted,
           the modemID/slotId, of the SIM card is also returned
           
           Returns                     Data type
           - SIM Count, modemId        tuple(int, int)
        """
        
        if not phone.graniteConnection.CommunicationAdapter:
            debug.err("getSimCount: No connection available")
            return 0
        
        
        req = MultiSimInfoGetReq(MultiSimInfo.MULTI_SIM_INFO_INSERTED_SIMS)

        success, resp = phone.graniteConnection.CommunicationAdapter.MessageApiSender.Send(req)

        if str(success) != 'Success':
            raise TestException('Failed to send MULTISIM_INFO_GET_REQ', phone)

        if not resp:
            raise TestException('Failed to receive MULTISIM_INFO_GET_RESP', phone)
        
        simCount = resp.Subblocks.Count

        modemID = None

        if simCount == 1:

            id = resp.Subblocks[0].DeviceId

            if id == 104:
                modemID = 2
            else:
                modemID = 1
            
        return resp.Subblocks.Count, modemID

    def setSimInfo(self, phone):
        if not phone.graniteConnection.CommunicationAdapter:
            debug.err("setSimInfo: No connection available")
            return  
        """Set first sim card for default data usage with MULTI_SIM_INFO_SET_REQ."""
        simIdField = MultiSimSbFlags.SimIdField(1)
        flagsField = MultiSimSbFlags.FlagsField(MultiSimInfoSbFlags.MULTI_SIM_INFO_FLAGS_DEFAULT_DATA)

        subBlock = MultiSimSbFlags(simIdField, flagsField)

        req = MultiSimInfoSetReq_002_000()
        req.Action = req.ActionField(MultiSimSetAction.MULTI_SIM_ACTION_SET)
        req.Subblocks.Add(subBlock)

        success, resp = phone.graniteConnection.CommunicationAdapter.MessageApiSender.Send(req)

        if str(success) != 'Success':
            raise TestException('Failed to send MULTI_SIM_INFO_SET_REQ', phone)

        if not resp:
            raise TestException('Failed to receive MULTI_SIM_INFO_SET_RESP', phone)

    def getSmsCenterNumber(self, phone, sim_id=1):
        """Gets sms center number with sx call

            Parameters                  Data type
            - sim_id                    int

        """

        simCount, modemId = self._simCheck(phone,sim_id)

        if not self.sx:
            self.sx = phone.sx

        sxString = """

        (send (get-sim-manager {0}) get-smsc-number)

        """
        debug.out('Reading sms center number from sim ' + str(sim_id))

        if simCount == 1 and modemId:
            sim_id = modemId


        resp = self.sx(String.Format(sxString, (sim_id - 1)))

        if resp == None:
            raise TestException('Failed to read sms center number from sim' + str(sim_id) + '. SX ERROR', phone)

        return resp

    def setSmsCenterNumber(self, phone, smsc_number, sim_id=1):
        """Sets sms center number with sx call

            Parameters                  Data type
            - smsc_number               str
            - sim_id                    int

        """
        
        if not isinstance(smsc_number, str):
            raise TestException('Incorrect data type for smsc_number; expecting str', phone)

        simCount, modemId = self._simCheck(phone,sim_id)

        if not self.sx:
            self.sx = phone.sx

        sxString = """

        (send (get-sim-manager {0}) set-smsc-name-number "" "{1}" "")
        (send (get-sim-manager {0}) get-smsc-number)

        """
        debug.out('Writing sms center number: ' + smsc_number + ' for sim ' + str(sim_id))

        if simCount == 1 and modemId:
            sim_id = modemId

        resp = self.sx(String.Format(sxString, (sim_id - 1), smsc_number))

        if not resp.StartsWith(smsc_number):
            raise TestException('Failed to write sms center number for sim' + str(sim_id) + '. SX ERROR', phone)

    def deleteProvisioningData(self, phone, configuration_context, sim_id=1):
        """Deletes provisioning settings data from given 
           configuration context, with given SIM

            Parameters                  Data type
            - configuration_context     int
            - sim_id                    int

            Returns                     Data type
            - True/False                bool
        """

        return self._provDelete(phone, False, configuration_context, sim_id)

    def deleteAllProvisioningData(self, phone, sim_id=1, delete_all = True):
        """Deletes all provisioning set for given SIM

            Parameters                  Data type
            - sim_id                    int
            - delete_all                bool

            Returns                     Data type
            - True/False                bool
        """

        return self._provDelete(phone, delete_all, 0, sim_id)

    def selectProvisioningData(self, phone, configuration_context, sim_id=1):
        """Selects provisioning settings data from given 
           configuration context, for given SIM

            Parameters                  Data type
            - configuration_context     int
            - sim_id                    int

            Returns                     Data type
            - True/False                bool
        """

        if not isinstance(configuration_context, int):
            raise TestException('Incorrect data type for configuration_context; expecting int', phone)

        self._simCheck(phone, sim_id)

        debug.out('Selecting provisioning data from configuration context: ' + str(configuration_context) \
            + ', from sim ' + str(sim_id) + '...')

        success = phone.provisioningSelectReq(sim_id, configuration_context) == 'ok'

        if not success:
            debug.out('Selecting provisioning data from: ' + str(configuration_context) \
                + ', for sim ' + str(sim_id) + ' failed')

        return success

    def readProvisioningData(self, phone, configuration_context, sim_id=1):
        """Reads provisioning settings data from given 
           configuration context, for given SIM

            Parameters                      Data type
            - configuration_context         int
            - sim_id                        int

            Returns                         Data type
            - Prov settings (json) object   list[dict]
        """

        if not isinstance(configuration_context, int):
            raise TestException('Incorrect data type for configuration_context; expecting int', phone)

        self._simCheck(phone,sim_id)

        debug.out('Reading provisioning data from configuration context: ' + str(configuration_context) \
            + ', from sim ' + str(sim_id) + '...')

        response, jsonBytes = phone.provisioningReadReq(sim_id, 'json', configuration_context)

        if response == 'ok':

            json = self.encoding.GetString(Array[Byte](jsonBytes)).TrimEnd('\0')

            return self.jsonToObject(json)
        
        else:
            raise TestException('Failed to read provisioning settings', phone)

    def writeFromJsonString(self, phone, jsonString, sim_id = 1, deletePrevious = True):
        """Writes provisioning settings data from json string, for given SIM(s)

            Parameters                      Data type
            - jsonString                    str
            - sim_id                        int

            Returns                         Data type
            - configuration_context         int
        """

        self._simCheck(phone,sim_id)
        
        if not isinstance(jsonString, str):
            raise TestException('Invalid type given for jsonString; expecting str', phone)

        if len(jsonString) == 0:
            raise TestException('Json string is empty', phone)

        # delete all previous provisioning data
        if deletePrevious:
            self.deleteAllProvisioningData(sim_id)

        debug.out('Writing provisioning data for sim ' + str(sim_id) + '...')

        response, configuration_context = phone.provisioningWriteReq(sim_id, 'json', self._stringToMessageData(jsonString))

        if response != 'ok':
            raise TestException('Writing provisionning data for sim' + str(sim_id) + ' failed', phone)

        #select the written provisioning data
        #self.selectProvisioningData(configuration_context, sim_id)

        return configuration_context

    def writeFromJsonFile(self, phone, jsonFilePath, sim_id = 1, deletePrevious = True):
        """Writes provisioning settings data from json file, for given SIM(s)

            Parameters                      Data type
            - jsonFilePath                  str
            - sim_id                        int

            Returns                         Data type
            - configuration_context         int
        """
        if not isinstance(jsonFilePath, str):
            raise TestException('Invalid type given for jsonFilePath; expecting str', phone)

        fi = FileInfo(jsonFilePath)

        if not fi.Exists:
            raise TestException(jsonFilePath + ' does not exist', phone)

        if fi.Length == 0:
            raise TestException(jsonFilePath + ' is empty', phone)

        return self.writeFromJsonString(phone,File.ReadAllText(jsonFilePath), sim_id, deletePrevious)

    def writeFromJsonFileToDefinedSims(self, phone, provSettingsFile = None, sim = 'all'):
        """Writes provisioning settings data from json file to defined SIMs in the phone

            Parameters                      Data type
            - phone                         phone class instance
            - provSettingsFile              provisioning settings json file path
            - sim                           1, 2 or 'all'
        """
        assert sim in [1, 2, 'all'], 'Invalid sim id given (%s), must be either 1, 2 or "all"' % str(sim)

        # skipped if TCP connection use
        if phone.getConnectionBusName() == 'TCP':
            return
        
        if not provSettingsFile:
            # use predefined NTN/BTN provisioning settings
            provSettingsFileDir = os.path.join(core.FW_conf['startup_path'], 'core\\data')
        else:
            # use given provisioning settings
            provSettingsFilePath = provSettingsFile
            assert os.path.isfile(provSettingsFilePath), 'Provisioning settings file missing: %s' % provSettingsFilePath

        operatorSim = False

        phoneName = phone.getName() != 'Main' and 'for remote phone' or ''

        for sim_id in range(2):
            if not provSettingsFile:
                # get sim country and operator code
                mccmnc = phone.srv.sim.getMccMnc(sim_id+1) 
            
                # NTN SIM
                if mccmnc == '24407':
                    fileName = 's40_ntn.json'

                    if core.FW_conf['settings'].TestRun.AutomaticProvisioningSettingsWrite:
                        debug.brf('Writing NTN provisioning settings to SIM %i %s' % ((sim_id+1), phoneName))
                # BTN SIM
                elif mccmnc == '46013':
                    fileName = 's40_btn.json'

                    if core.FW_conf['settings'].TestRun.AutomaticProvisioningSettingsWrite:
                        debug.brf('Writing BTN provisioning settings to SIM %i %s' % ((sim_id+1), phoneName))
                # some other SIM --> no settings will be written
                else:
                    if mccmnc != '':
                        operatorSim = True
                    continue

                provSettingsFilePath = os.path.join(provSettingsFileDir, fileName)
                assert os.path.isfile(provSettingsFilePath), 'Provisioning settings file missing: %s' % provSettingsFilePath
            else:
                # check SIM id
                if sim != 'all' and sim != sim_id+1:
                    continue

                debug.brf('Writing provisioning settings to SIM %i from %s %s' % ((sim_id+1), provSettingsFilePath, phoneName))

            # when writing NTN/BTN settings, check setting whether we should write the settings
            if not provSettingsFile and not core.FW_conf['settings'].TestRun.AutomaticProvisioningSettingsWrite:
                continue

            # delete previous provisioning data
            self.deleteAllProvisioningData(phone, sim_id + 1, False)

            # write provisioning data
            self.writeFromJsonFile(phone, provSettingsFilePath, sim_id + 1, deletePrevious = False)

        # set first sim for default data usage
        self.setSimInfo(phone)

        # Set POX SIP Proxy type based on the SIM card used in Main phone.
        # With SIPMGW, 10 000 short numbers available for mobile calling within NTN network
        # With OpenSIPS mobile calls to operator SIM cards are also possible (~20 numbers allocated for this SIP proxy)
        if phone.getName() == 'Main':
            if operatorSim:
                core.FW_conf['settings'].TestRun.POXSIPProxy = 'OpenSIPS'
            else:
                core.FW_conf['settings'].TestRun.POXSIPProxy = 'SIPMGW'

    def writeFromJsonObject(self, phone, jsonObject, sim_id = 1):
        """Writes provisioning settings data from json object, for given SIM(s)

            Parameters                      Data type
            - jsonObject                    list[dict]
            - sim_id                        int

            Returns                         Data type
            - configuration_context         int
        """
        return self.writeFromJsonString(phone, self.objectToJson(jsonObject), sim_id)

    def writeFromWbxmlFile(self, phone, wbxmlFilePath, sim_id = 1):
        """Writes provisioning settings data from wbxml file, for given SIM(s)

            Parameters                      Data type
            - wbxmlFilePath                 str
            - sim_id                        int

            Returns                         Data type
            - configuration_context         int
        """

        return self.writeFromJsonString(phone, self.wbxmlToJson(wbxmlFilePath), sim_id)

    def wbxmlToJsonObject(self, phone, wbxmlFilePath):
        """Converts wbxml data to json object

            Parameters                      Data type
            - wbxmlFilePath                 str

            Returns                         Data type
            - json object                   list[dict]
        """
        
        return self.jsonToObject(self.wbxmlToJson(wbxmlFilePath))

    def wbxmlToJson(self, wbxmlFilePath):
        """Converts wbxml data to json string

            Parameters                      Data type
            - wbxmlFilePath                 str

            Returns                         Data type
            - json string                   str
        """
        
        if not isinstance(wbxmlFilePath, str):
            raise TestException('Invalid type given for wbxmlFilePath; expecting str')

        fi = FileInfo(wbxmlFilePath)

        if not fi.Exists:
            raise TestException(wbxmlFilePath + ' does not exist')

        if fi.Length == 0:
            raise TestException(wbxmlFilePath + ' is empty')

        return wbxml2json.convert(wbxmlFilePath)

    def jsonToObject(self, jsonString):
        """Converts json string json object

            Parameters                      Data type
            - jsonString                    str

            Returns                         Data type
            - (json) object                 list[dict]
        """
        if not isinstance(jsonString, str):
            raise TestException('Invalid type given for jsonString; expecting str')

        if len(jsonString) == 0:
            raise TestException('jsonString cannot be empty')

        if not self.serializer:
            self.serializer = JavaScriptSerializer()

        return self._toPythonType(self.serializer.Deserialize[object](jsonString))

    def objectToJson(self, jsonObject):
        """Converts (json) object to json string

            Parameters                      Data type
            - jsonObject                    list[dict]

            Returns                         Data type
            - json                          str
        """

        if len(jsonObject) == 0:
            raise TestException('jsonObject cannot be empty')

        if not self.serializer:
            self.serializer = JavaScriptSerializer()

        return self.serializer.Serialize(jsonObject)

    def _provDelete(self, phone, delete_all, configuration_context, sim_id=1):
        """Deletes provisioning settings data from given 
           configuration context, with given SIM

            Parameters                  Data type
            - delete_all                bool
            - configuration_context     int (do not care if delete_all is set to True)
            - sim_id                    int

            Returns                     Data type
            - True/False                bool
        """
        
        if not isinstance(configuration_context, int):
            raise TestException('Incorrect data type for configuration_context; expecting int', phone)

        self._simCheck(phone, sim_id)

        if not delete_all:
            debug.out('Deleting provisioning data from configuration context: ' + str(configuration_context) \
                + ', from sim ' + str(sim_id) + '...')
        else:
            debug.out('Deleting all provisioning data from sim ' + str(sim_id) + '...')
        
        success = phone.provisioningDeleteReq(sim_id, delete_all, configuration_context) == 'ok'

        if not success:
            if not delete_all:
                debug.out('Deleting provisioning data from configuration context: ' + str(configuration_context) \
                    + ', from sim ' + str(sim_id) + ' failed; there might be no data to delete')
            else:
                debug.out('Deleting all provisioning data from sim' + str(sim_id) \
                     + ' failed; there might be no data to delete')

        return success

    def _simCheck(self, phone, sim_id):
        """Verifies the given sim id against the amount 
           of sim cards attahed to device

           Parameters                     Data type
           - sim_id                       int
           
           Returns                     Data type
           - SIM Count, modemId        tuple(int, int)
        """

        if not isinstance(sim_id, int):
            raise TestException('Incorrect data type for sim_id; expecting int', phone)
        
        simCount, modemId = self.getSimCount(phone)

        if sim_id > simCount:
            raise TestException('Invalid sim id: (' + str(sim_id) + '). Amount of attached sim cards is ' \
                + str(simCount), phone)
        
        elif sim_id < 1:
            raise TestException('Invalid sim id: (' + str(sim_id) + ').', phone)

        return simCount, modemId

    def _stringToMessageData(self, text):
        """Returns a given string as list of integers

            Parameters                      Data type
            - text                          str

            Returns                         Data type
            - string as list of integers    list [int]
        """
        
        return [int(b) for b in self.encoding.GetBytes(text)]

    def _toPythonType(self, obj):
        """Converts .NET dictionary and array types to python types (dict and list)
           
           Parameters                      Data type
           - obj                           object (.NET types: Array[Dictionary[str, object]])
           
           Returns                         object (Python types: list[dict])      
        """
        
        if obj == None:
            return None

        if obj.GetType().IsArray:
            obj = list(obj)

        elif isinstance(obj, Dictionary[str, object]):
            obj = dict(obj)

        if isinstance(obj, list):
            return [self._toPythonType(i) for i in obj]
     
        elif isinstance(obj, dict):
            d = {}
            for i in obj.Keys:
                d.Add(i, self._toPythonType(obj[i]))
            return d

        return obj

    def _getMCCMNCForSIM(self, phone, slot = 0):
        """Returns mcc and mnc values for given sim index."""
        mccmnc = ''

        for code in ['mcc', 'mnc']:
            value = phone.sx(
            """
            (define sim-manager (get-sim-manager %s))
            (define sim-plmn (send sim-manager get-plmn))

            (when
                (and
                    (equal? (send sim-manager get-sim-state) 'sim-ready)
                    sim-plmn
                )
                (string-append (send sim-plmn get-%s))
            )
            """ % (slot, code), doNotReport = True)

            mccmnc += value

        return mccmnc 

