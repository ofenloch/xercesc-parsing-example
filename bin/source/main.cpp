#include <main.h>

int main(int argc, char *argv[])
{
  CHello myGreeter;

  myGreeter.sayHello();

  myGreeter.sayHello("Hello, World!");

  if (argc <= 1)
  {
    std::cout << "Usage: " << argv[0] << " <xml file>" << std::endl
              << std::endl;
    std::cout << "       "
              << "The <xml file> is mandatory." << std::endl;
    return 1;
  }
  std::string filename = argv[1];

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
    std::cout << "Exception message is:" << std::endl
              << message << std::endl;
    xercesc::XMLString::release(&message);
    return -1;
  }
  catch (const xercesc::XMLException &toCatch)
  {
    char *message = xercesc::XMLString::transcode(toCatch.getMessage());
    std::cout << "Exception message is:" << std::endl
              << message << std::endl;
    xercesc::XMLString::release(&message);
    return -1;
  }
  catch (const xercesc::DOMException &toCatch)
  {
    char *message = xercesc::XMLString::transcode(toCatch.msg);
    std::cout << "Exception message is:" << std::endl
              << message << std::endl;
    xercesc::XMLString::release(&message);
    return -1;
  }
  // terminate
  xercesc::XMLPlatformUtils::Terminate();
  return 0;

  return 0;
} // int main(int argc, char *argv[])