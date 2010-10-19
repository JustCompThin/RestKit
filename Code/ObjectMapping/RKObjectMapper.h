//
//  RKObjectMapper.h
//  RestKit
//
//  Created by Blake Watters on 3/4/10.
//  Copyright 2010 Two Toasters. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RKObjectMappable.h"
#import "RKObjectPropertyInspector.h"
#import "../Support/RKParser.h"

/**
 * Define the object mapping formats
 */
typedef enum {
	RKMappingFormatXML = 0,
	RKMappingFormatJSON
} RKMappingFormat;

@interface RKObjectMapper : NSObject {
	NSMutableDictionary* _elementToClassMappings;
	RKMappingFormat _format;
	RKObjectPropertyInspector* _inspector;
	NSArray* _dateFormats;
	NSTimeZone* _remoteTimeZone;
	NSTimeZone* _localTimeZone;
	NSString* _errorsKeyPath;
	NSString* _errorsConcatenationString;
}

/**
 * The format the mapper is using
 */
@property(nonatomic, assign) RKMappingFormat format;

/**
 * An array of date format strings to attempt to parse mapped date properties with
 *
 * Initialized with a default pair of timestamp and date strings suitable for
 * parseing time and date objects returned from Rails applications
 */
@property(nonatomic, retain) NSArray* dateFormats;

/**
 * The time zone of the remote system. Date strings pulled from the remote source
 * will be considered to be local to this time zone when mapping.
 *
 * Defaults to UTC
 */
@property(nonatomic, retain) NSTimeZone* remoteTimeZone;

/**
 * The target time zone to map dates to.
 *
 * Defaults to the local time zone
 */
@property(nonatomic, retain) NSTimeZone* localTimeZone;

/*
 * This defines the key path to look for errors in a string. defaults to @"errors"
 */
@property (nonatomic, copy) NSString* errorsKeyPath;

/*
 * This string is used to concatenate the errors returned in a string. defaults to @", "
 */
@property (nonatomic, copy) NSString* errorsConcatenationString;

/**
 * Register a mapping for a given class for an XML element with the given tag name
 * will blow up if the class does not respond to elementToPropertyMappings and elementToRelationshipMappings
 */
- (void)registerClass:(Class<RKObjectMappable>)aClass forElementNamed:(NSString*)elementName;

///////////////////////////////////////////////////////////////////////////////
// Core Mapping API

/**
 * Digests a string into an object graph and returns mapped model objects from the objects
 * serialized in the string
 */
- (id)mapFromString:(NSString*)string;

/**
 * Digests a string (such as an error response body) in to an NSError.
 * It should only be called for a string you know contains an error.
 */
- (NSError*)parseErrorFromString:(NSString*)string;

/**
 * Sets the properties and relationships serialized in the string into the model instance
 * provided
 */
- (void)mapObject:(id)model fromString:(NSString*)string;

///////////////////////////////////////////////////////////////////////////////
// Object Mapping API

/**
 * Sets the properties and relationships serialized in the dictionary into the model instance
 * provided
 */
- (void)mapObject:(id)model fromDictionary:(NSDictionary*)dictionary;

/**
 * Returns mapped model(s) from the data serialized in the dictionary into the model instance
 * provided
 */
- (id)mapObjectFromDictionary:(NSDictionary*)dictionary;

/**
 * Constructs an array of mapped model objects from an array of dictionaries
 * containing serialized objects
 */
- (NSArray*)mapObjectsFromArrayOfDictionaries:(NSArray*)array;

///////////////////////////////////////////////////////////////////////////////
// Non-element based object mapping

/**
 * Map the objects in a given payload string to a particular object class, optionally filtering
 * the parsed result set via a keyPath before mapping the results.
 */
- (id)mapFromString:(NSString *)string toClass:(Class)class keyPath:(NSString*)keyPath;

/**
 * Map an array of object dictionary representations to instances of a particular
 * object class
 */
- (NSArray*)mapObjectsFromArrayOfDictionaries:(NSArray*)array toClass:(Class)class;

/**
 * Parse a string using the appropriate parser and return the results
 */
- (id)parseString:(NSString*)string;

@end
