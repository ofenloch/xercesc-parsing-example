#include <main.h>

int serializeDOM(xercesc::DOMNode *node)
{

  XMLCh tempStr[100];
  xercesc::XMLString::transcode("LS", tempStr, 99);
  xercesc::DOMImplementation *impl = xercesc::DOMImplementationRegistry::getDOMImplementation(tempStr);
  xercesc::DOMLSSerializer *theSerializer = ((xercesc::DOMImplementationLS *)impl)->createLSSerializer();

  // optionally you can set some features on this serializer
  if (theSerializer->getDomConfig()->canSetParameter(xercesc::XMLUni::fgDOMWRTDiscardDefaultContent, true))
    theSerializer->getDomConfig()->setParameter(xercesc::XMLUni::fgDOMWRTDiscardDefaultContent, true);

  if (theSerializer->getDomConfig()->canSetParameter(xercesc::XMLUni::fgDOMWRTFormatPrettyPrint, true))
    theSerializer->getDomConfig()->setParameter(xercesc::XMLUni::fgDOMWRTFormatPrettyPrint, true);

  // optionally you can implement your DOMLSSerializerFilter (e.g. MyDOMLSSerializerFilter)
  // and set it to the serializer
  // xercesc::DOMLSSerializer *myFilter = new myDOMLSSerializerFilter();
  // theSerializer->setFilter(myFilter);

  // optionally you can implement your DOMErrorHandler (e.g. MyDOMErrorHandler)
  // and set it to the serializer
  // xercesc::DOMErrorHandler *errHandler = new myDOMErrorHandler();
  // theSerializer->getDomConfig()->setParameter(xercesc::XMLUni::fgDOMErrorHandler, myErrorHandler);

  // StdOutFormatTarget prints the resultant XML stream
  // to stdout once it receives any thing from the serializer.
  xercesc::XMLFormatTarget *myFormTarget = new xercesc::StdOutFormatTarget();
  xercesc::DOMLSOutput *theOutput = ((xercesc::DOMImplementationLS *)impl)->createLSOutput();
  theOutput->setByteStream(myFormTarget);

  try
  {
    // do the serialization through DOMLSSerializer::write();
    theSerializer->write(node, theOutput);
  }
  catch (const xercesc::XMLException &toCatch)
  {
    char *message = xercesc::XMLString::transcode(toCatch.getMessage());
    std::cout << "Exception message is: \n"
              << message << "\n";
    xercesc::XMLString::release(&message);
    return -1;
  }
  catch (const xercesc::DOMException &toCatch)
  {
    char *message = xercesc::XMLString::transcode(toCatch.msg);
    std::cout << "Exception message is: \n"
              << message << "\n";
    xercesc::XMLString::release(&message);
    return -1;
  }
  catch (...)
  {
    std::cout << "Unexpected Exception \n";
    return -1;
  }

  theOutput->release();
  theSerializer->release();
  // delete myErrorHandler and myFilter if they were created:
  // delete myErrorHandler;
  // delete myFilter;

  delete myFormTarget;
  return 0;
}

int main(int argc, char *argv[])
{
  if (argc <= 1)
  {
    std::cout << "Usage: " << argv[0] << " <xml file>" << std::endl
              << std::endl;
    std::cout << "       "
              << "The <xml file> is mandatory." << std::endl;
    return 1;
  }
  std::string filename = argv[1];
  std::cout << "Parsing file \"" << filename << "\" ..." << std::endl;

  // Independent of the API you want to use, DOM, SAX, or SAX2, your application
  // must initialize the Xerces system before using the API, and terminate it
  // after you are done. This is achieved by the following code:
  try
  {
    xercesc::XMLPlatformUtils::Initialize();
    // Do not forget to call
    //    xercesc::XMLPlatformUtils::Terminate();
    // when you're done.
  }
  catch (const xercesc::XMLException &toCatch)
  {
    // Do your failure processing here
    return 1;
  }

  xercesc::XercesDOMParser *m_parser = new xercesc::XercesDOMParser();
  m_parser->setValidationScheme(xercesc::XercesDOMParser::Val_Always);
  m_parser->setDoNamespaces(true); // optional
  xercesc::ErrorHandler *m_errorHandler = (xercesc::ErrorHandler *)new xercesc::HandlerBase();
  m_parser->setErrorHandler(m_errorHandler);
  // Tell the parser to create entity reference nodes (defaults to false):
  // NOTE: Setting this to false will cause the parser to resolve entities!
  // The documentation is either wrong or very misleading.
  m_parser->setCreateEntityReferenceNodes(false);

  xercesc::DOMDocument *m_document = nullptr;

  try
  {
    m_parser->parse(filename.c_str());
    m_document = m_parser->getDocument();
    std::cout << "Parsed file \"" << filename << "\" :-))" << std::endl;
    xercesc::DOMDocumentType *docType = m_document->getDoctype();
    char *message = xercesc::XMLString::transcode(docType->getName());
    std::cout << "DOMDocumentType is \"" << message << "\"" << std::endl;
    xercesc::DOMNodeList *children = m_document->getChildNodes();
    if (children != nullptr)
    {
      int nChildren = children->getLength();
      std::cout << "document has " << nChildren << " child node(s):" << std::endl;
      xercesc::XMLString::release(&message);
      for (int i = 0; i < nChildren; i++)
      {
        xercesc::DOMNode *child = children->item(i);
        std::cout << "  " << i + 1 << " : " << xercesc::XMLString::transcode(child->getNodeName()) << std::endl;
      }
    }
    else
    {
      std::cout << "document has no  child nodes" << std::endl;
    }
  }
  catch (const xercesc::SAXParseException &toCatch)
  {
    char *message = xercesc::XMLString::transcode(toCatch.getMessage());
    std::cout << "SAXParseException: message is:" << std::endl
              << message << std::endl;
    xercesc::XMLString::release(&message);
    return -1;
  }
  catch (const xercesc::XMLException &toCatch)
  {
    char *message = xercesc::XMLString::transcode(toCatch.getMessage());
    std::cout << "XMLException: message is:" << std::endl
              << message << std::endl;
    xercesc::XMLString::release(&message);
    return -1;
  }
  catch (const xercesc::DOMException &toCatch)
  {
    char *message = xercesc::XMLString::transcode(toCatch.msg);
    std::cout << "DOMException: message is:" << std::endl
              << message << std::endl;
    xercesc::XMLString::release(&message);
    return -1;
  }

  serializeDOM(m_document);

  // terminate
  xercesc::XMLPlatformUtils::Terminate();
  return 0;

  return 0;
} // int main(int argc, char *argv[])