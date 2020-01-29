#include "pugixml.hpp"

namespace Util {
    /**
     * @brief This a utility struct that expands pugi functionality. Used for converting XMLs to a string.
     * 
     */
    struct XMLStringWriter : pugi::xml_writer {
        /**
         * @brief The string that contains the XML.
         * 
         */
        std::string stringData;

        /**
         * @brief Adds the XML data to the internal string.
         * 
         * @param data The XML data.
         * @param size The size of the XML data.
         */
        virtual void write(const void *data, size_t size) {
            stringData.append(static_cast<const char *>(data), size);
        }
    };
} // namespace PugiXmlAdditions